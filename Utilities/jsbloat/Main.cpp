#include <iostream>
#include <Config.hpp>
#include <Strings.hpp>

void printHelp(const char *progname) {
	
}

int main(int argc, char *argv[]) {
	cfg::Args args;
	Logger log;
	
	args.setupArguments("hf!r!");
	
	if (not args.parse(argc, argv)) {
		printHelp();
		return 1;
	}
	
	std::string filename = args.getArgumentValue('f');
	std::string rulename = args.getArgumentValue('r');
	
	cfg::Csv csv;
	if (not csv.load(rulename)) {
		return 2;
	}
	
	std::string file;
	try {
		std::ifstream load (filename);
		load.seekg(0, load.end);
		std::size_t len = load.tellg();
		load.seekg(0, load.begin);
		
		load.read(file, len);
		
		load.close();
		load.clear();
	}
	catch (std::exception &e) {
		std::cerr << e.what() << std::endl;
		return 3;
	}
	
	// Apply rules
	
	// Export file
	
	return 0;
}