#include <iostream>
#include <fstream>
#include <regex>
#include <unordered_map>

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
	
	if (id[last] == 'z') {
		id += 'a';
	}
	else {
		id[last]++;
	}
}

void replaceIds(const std::unordered_map<std::string, std::string> &ids, std::string &file) {
	for (auto id : ids) {
		replaceAll(file, id.first, id.second);
	}
}

int main(int argc, char *argv[]) {
	// Grab file names
	std::vector<std::string> filenames (argc - 1);
	for (int i = 1; i < argc; i++) {
		filenames[i - 1] = std::string(argv[i]);
	}
	
	// Load files and concatenate into single result
	std::string file;
	for (auto filename : filenames) {
		try {
			std::ifstream load(filename, std::ios::binary);
			
			// Get size of file
			load.seekg(0, std::ios::end);
			std::size_t len = load.tellg();
			load.seekg(0, std::ios::beg);
			
			std::cerr << "allocating buf\n";
			
			// Allocate buffer
			char *buf = new char[len];
			
			// Read buffer and add it to file
			load.read(buf, len);
			
			std::cerr << "allocating str\n";
			
			file += std::string(buf, len);
			
			delete[] buf;
			
			file += ';'; // This will prevent invalid char in code
			
			load.close();
			load.clear();
		}
		catch (std::exception &e) {
			std::cerr << e.what() << "\n";
			return 1;
		}
	}
	
	std::cout << "Filelen: " << file.size() << "\n";
	
	std::smatch found;
	
	std::unordered_map<std::string, std::string> ids;
	
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
	
	std::ofstream save ("concat.js", std::ios::binary);
	save.write(file.c_str(), file.size());
	save.close();
	save.clear();
	
	return 0;
}