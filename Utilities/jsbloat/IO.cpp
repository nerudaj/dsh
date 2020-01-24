#include "IO.hpp"

#include <fstream>

SourceFile io::concatenateSourceFiles(const std::vector<std::string> &filenames) {
	SourceFile file;

	for (auto filename : filenames) {
		SourceFile inputFile;
        inputFile.loadFromFile(filename);
        file.concatenate(inputFile);
	}
	
	return file;
}

std::vector<std::string> io::loadHintFile(const std::string &filename) {
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