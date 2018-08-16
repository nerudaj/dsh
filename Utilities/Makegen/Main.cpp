#include <iostream>
#include <fstream>
#include <ciso646>
#include "Makegen.hpp"
#include <Config.hpp>
#include <Logger.hpp>

void printHelp(char *progname) {
	std::cout << "Usage:\n";
	std::cout << "\t" << progname << " [OPTIONS]\n\n";
	
	std::vector<std::pair<std::string, std::string>> rows = {
		{"-h", "Prints this text"},
		{"-g", "Generate *.in file. Default name is Makefile.in" },
		{"-i", "Set the name of the infile. Example: '-i infile.in'. Default: 'Makefile.in'"},
		{"-m", "Set the name of the produced Makefile. Example: '-o Makefile.project'. Default: 'Makefile'"},
		{"-t", "Set the type of the project (library|binary). Default: 'binary'"}
	};
	
	for (auto row : rows) {
		std::cout << "\t" << row.first << ": " << row.second << "\n";
	}
	
	std::cout << "\n";
	std::cout << "Details: Running this program without -g parameter will try to generate valid Makefile by loading the infile into the memory, parsing it and then producing appropriate Makefile.\n\n";
}

int main(int argc, char *argv[]) {
	//Logger::loglevel = 4;
	cfg::Args args;
	args.setupArguments("hgi:m:t:");
	
	if (not args.parse(argc, argv)) {
		printHelp(argv[0]);
		return 1;
	}
	
	if (args.isSet('h')) {
		printHelp(argv[0]);
		return 0;
	}
	
	std::string infile = "Makefile.in", outfile = "Makefile", type = "binary";
	int generateWhich = 1; // 0 - infile, 1 - outfile
	
	if (args.isSet('i')) infile = args.getArgumentValue('i').asString();
	if (args.isSet('m')) outfile = args.getArgumentValue('o').asString();
	if (args.isSet('t')) {
		type = args.getArgumentValue('t').asString();
		Logger::info("Makegen", "Project type is " + type);
	}
	if (args.isSet('g')) {
		Logger::info("Makegen", "Generating infile");
		generateWhich = 0;
	}
	
	Makegen::Mode mode = Makegen::Mode::Binary;
	if (type != "binary" && type != "library") {
		Logger::warning("Makegen", "Unknown type of the project. Fallback to default (binary)");
	}
	if (type == "library") mode = Makegen::Mode::Library;
	
	if (generateWhich == 0) {
		return Makegen::generateInfile(infile, mode);
	}
	
	return Makegen::generateMakefile(infile, outfile);
}