#pragma once

#include <utility>
#include <string>
#include <vector>

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