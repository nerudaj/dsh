#include "SourceFile.hpp"
#include "Logger.hpp"

#include <Strings.hpp>
#include <fstream>

void SourceFile::replaceStrings(const std::unordered_map<std::string, std::string> &strings) {
    for (auto item : strings) {
        Strings::replaceAll(content, item.first, item.second);
    }
}

void SourceFile::replaceString(const std::string &from, const std::string &to) {
    Strings::replaceAll(content, from, to);
}

void SourceFile::concatenate(const SourceFile &other) {
    content += ';';
    content += other.content;
}

void SourceFile::loadFromFile(const std::string &filename) {
    std::ifstream load(filename, std::ios::binary);
		
    logger.debug("loadFromFile", "Loading file " + filename);

    if (!load.good()) {
        logger.error("loadFromFile", "load object is not good");
        exit(1);
    }

    // Get size of file
    load.seekg(0, std::ios::end);
    std::size_t len = load.tellg();
    load.seekg(0, std::ios::beg);

    logger.debug("loadFromFile", "File size is " + std::to_string(len));
    
    // Allocate buffer
    char *buf = new char[len];
    if (buf == NULL) {
        logger.error("loadFromFile", "Could not allocate " + std::to_string(len) + "B of memory");
        exit(1);
    }
		
    // Read buffer and add it to file
    load.read(buf, len);
				
    content = std::string(buf, len);
		
    delete[] buf;
				
    load.close();
    load.clear();
}

void SourceFile::saveToFile(const std::string &filename) {
    std::ofstream save (filename, std::ios::binary);
	save.write(content.c_str(), content.size());
	save.close();
	save.clear();
}