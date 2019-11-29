#include <iostream>
#include <fstream>
#include <regex>
#include <unordered_map>
#include <Config.hpp>

class Logger {
public:
	void error(const std::string &module, const std::string &msg) {
		std::cerr << "ERROR: " << module << ": " << msg << std::endl;
	}

	void warning(const std::string &module, const std::string &msg) {
		std::cerr << "WARNING: " << module << ": " << msg << std::endl;
	}

	void info(const std::string &module, const std::string &msg) {
		std::cout << "INFO: " << module << ": " << msg << std::endl;
	}

	void debug(const std::string &module, const std::string &msg) {
		std::cout << "DEBUG: " << module << ": " << msg << std::endl;
	}

	void setLoggingLevel(int i) {}
};

Logger logger;

struct RuleForStatic {
	std::regex findFunction;
	std::regex findName;
	char prefix;
};

std::vector<RuleForStatic> rules = {
	{ std::regex("\'static\'\\; function [_a-zA-Z][_a-zA-Z0-9]*"), std::regex("\'static\'\\; function "), 'f' },
	{ std::regex("\'static\'\\; [_a-zA-Z][_a-zA-Z0-9]*\\.prototype\\.[_a-zA-Z][_a-zA-Z0-9]*"), std::regex("\'static\'\\; [_a-zA-Z][_a-zA-Z0-9]*\\.prototype\\."), 'p' },
	{ std::regex("\'static\'\\; var [_a-zA-Z][_a-zA-Z0-9]*"), std::regex("\'static\'\\; var "), 'v' } 
};

std::string IDCODES = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVXYZ012345678_";

void replaceAll(std::string &str, const std::string &from, const std::string &to) {
	if(from.empty()) return;
	
	size_t start_pos = 0;
	while((start_pos = str.find(from, start_pos)) != std::string::npos) {
		str.replace(start_pos, from.length(), to);
		start_pos += to.length(); // In case 'to' contains 'from', like replacing 'x' with 'yx'
	}
}

void permutateObfuscatedId(std::string &id) {
	auto last = id.size() - 1;
	auto loc = IDCODES.find(id[last]);
	
	if (IDCODES[loc] == '_') {
		id += 'a';
	}
	else {
		id[last] = IDCODES[++loc];
	}
}

void replaceIds(const std::unordered_map<std::string, std::string> &ids, std::string &file) {
	for (auto id : ids) {
		if (id.second[0] != 'v') {
			replaceAll(file, id.first + "(", id.second + "(");
			replaceAll(file, id.first + " ", id.second + " ");
			replaceAll(file, id.first + ",", id.second + ",");
			replaceAll(file, id.first + ";", id.second + ";");
			replaceAll(file, " " + id.first + ".", " " + id.second + ".");
			replaceAll(file, "\n" + id.first + ".", "\n" + id.second + ".");
		}
		else {
			replaceAll(file, id.first, id.second);
		}
	}
}

void printHelp(const std::string &progname) {
	std::cout << "Usage:\n";
	std::cout << "\t" << progname << " [OPTIONS] file1 file2 file3 ...\n\n";
	
	std::vector<std::pair<std::string, std::string>> rows = {
		{"-h", "Prints this text"},
		{"-o", "Set the name of output file. Default: concat.min.js"},
		{"-v", "Set verbosity level (1, 2, 3 or 4). Default: 2"},
		{"-H", "Set name of hint file. Default: hints.txt"}
	};
	
	for (auto row : rows) {
		std::cout << "\t" << row.first << ": " << row.second << "\n";
	}
	
	std::cout << "\n";
	std::cout << "Details: This program will load all files specified as positional arguments, concatenates them and perform several optimizations normal minifier cannot do.\nNamely it will minify names of all methods and global variables that have 'static'; written before their definitions. Please note that you must not have two identical identifiers in different namespaces with only one of them being static (minified will be both).\nSecond optimization relies on existence of function ID in your code. Any DOM id that is wrapped into call to ID function will be minified and calls to ID will be removed, as well as the function itself.\n\n";
}

std::string loadSourceCodes(const std::vector<std::string> &filenames) {
	std::string file;
	for (auto filename : filenames) {
		//try {
			std::ifstream load(filename, std::ios::binary);
			
			// Get size of file
			load.seekg(0, std::ios::end);
			std::size_t len = load.tellg();
			load.seekg(0, std::ios::beg);
			
			logger.debug("Loading file", "Allocating buffer");
			
			// Allocate buffer
			char *buf = new char[len];
			
			// Read buffer and add it to file
			load.read(buf, len);
			
			logger.debug("Loading file", "Allocating string");
			
			file += std::string(buf, len);
			
			delete[] buf;
			
			file += ';'; // This will prevent invalid char in code
			
			load.close();
			load.clear();
		/*}
		catch (std::exception &e) {
			std::cerr << e.what() << "\n";
			return 1;
		}*/
	}
	
	logger.debug("Loading done", "Concatenated size: " + std::to_string(file.size()));
	
	return file;
}

std::vector<std::string> loadHints(const std::string &filename) {
	std::vector<std::string> result;
	
	std::ifstream load(filename);
	
	std::string buffer;
	while (load >> buffer) {
		result.push_back(buffer);
	}
	
	load.close();
	load.clear();
	
	return result;
}

void obfuscateStatics() {}

void obfuscateIdStrings() {}

void obfuscateEnumStrings(){}

void obfuscateHinted(const std::vector<std::string> &hints, std::string &file) {
	std::string obfuscatedId = "a";
	
	for (auto hint : hints) {
		replaceAll(file, hint, "i" + obfuscatedId);
		permutateObfuscatedId(obfuscatedId);
	}
}

int main(int argc, char *argv[]) {
	cfg::Args args;
	args.setupArguments("ho:v:H:");

	try {
		args.parse(argc, argv);
	}
	catch (...) {
		printHelp(argv[0]);
		return 1;
	}

	if (args.isSet('h')) {
		printHelp(argv[0]);
		return 1;
	}
	
	if (args.isSet('v')) {
		logger.setLoggingLevel(args.getArgumentValue('v').asInt());
	}
	else {
		logger.setLoggingLevel(2);
	}

	// Grab file names
	std::vector<std::string> filenames = args.getPositionalArguments();
	
	if (filenames.empty()) {
		logger.warning("jsbloat", "No input filenames given, nothing to do");
		return 0;
	}

	auto file = loadSourceCodes(filenames);
	
	std::smatch found;
	
	std::unordered_map<std::string, std::string> ids;
	
	replaceAll(file, " (", "(");
	
	// Process all statics
	for (auto rule : rules) {
		std::string filecopy = file;
		std::string obfuscatedId = "a";
		
		while (std::regex_search(filecopy, found, rule.findFunction)) {
			for (auto match : found) {
				std::string id = std::regex_replace(std::string(match), rule.findName, "");
				
				if (ids.find(id) != ids.end()) continue;
				
				ids[id] = rule.prefix + obfuscatedId;
				
				std::cout << id << " --> " << rule.prefix << obfuscatedId << std::endl;
				
				permutateObfuscatedId(obfuscatedId);
			}
			
			filecopy = found.suffix().str();
		}
	}
	
	replaceIds(ids, file);
	ids.clear();
	
	// ID()
	std::regex findIds("ID\\(\'[_a-zA-Z0-9]+\'\\)");
	std::string filecopy = file, obfuscatedId = "a";
	while (std::regex_search(filecopy, found, findIds)) {
		for (auto match : found) {
			std::string raw = std::string(match);
			std::string id = raw.substr(4, raw.size() - 6);
			
			if (ids.find(id) != ids.end()) continue;
			
			ids[id] = obfuscatedId;
			
			std::cout << id << " --> " << obfuscatedId << "\n";
			
			permutateObfuscatedId(obfuscatedId);
		}
		
		filecopy = found.suffix().str();
	}
	
	for (auto id : ids) {
		replaceAll(file, "ID('" + id.first + "')", "'" + id.second + "'");
	}
	replaceAll(file, "function ID(id) {return id;}", ""); // Remove marker function
	
	// ENUM()
	std::unordered_map<std::string, int> enums;
	std::regex findEnums("ENUM\\(\'[_a-zA-Z0-9]+\'\\)");
	filecopy = file;
	int idCounter = 0;
	while (std::regex_search(filecopy, found, findEnums)) {
		for (auto match : found) {
			std::string raw = std::string(match);
			std::string id = raw.substr(6, raw.size() - 8);
			
			if (enums.find(id) != enums.end()) continue;
			
			enums[id] = idCounter;
			
			std::cout << id << " ---> " << idCounter << "\n";
			idCounter++;
		}
		
		filecopy = found.suffix().str();
	}
	
	// TODO: replace
	for (auto id : enums) {
		replaceAll(file, "ENUM('" + id.first + "')", std::to_string(id.second));
	}
	replaceAll(file, "function ENUM(id) {return id;}", "");
	
	replaceAll(file, "'static';", "");
	
	if (args.isSet('H')) {
		auto hintfile = args.getArgumentValue('H').asString();
		auto hints = loadHints(hintfile);

		obfuscateHinted(hints, file);
	}
	
	logger.debug("Loading done", "Minified size: " + std::to_string(file.size()));
	
	std::string outfilename = "concat.min.js";
	if (args.isSet('o')) outfilename = args.getArgumentValue('o').asString();
	
	std::ofstream save (outfilename, std::ios::binary);
	save.write(file.c_str(), file.size());
	save.close();
	save.clear();
	
	return 0;
}