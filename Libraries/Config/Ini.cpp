#include "Ini.hpp"
#include <fstream>
#include <regex>

using namespace cfg;

bool Ini::isSectionHeader(const std::string &line) {
	return std::regex_match (line, std::regex("\\[.+\\]"));
}

bool Ini::isKeyValuePair(const std::string &line) {
	return std::regex_match (line, std::regex(".+=.*"));
}

void Ini::getSectionIdentifier(const std::string &line, std::string &dst) {
	dst = line.substr(1, line.length() - 2);
}

void Ini::getKeyValue(const std::string &line, std::string &dstKey, std::string &dstValue) {
	auto delimiterPosition = line.find('=');
	dstKey = line.substr(0, delimiterPosition);
	dstValue = line.substr(delimiterPosition + 1, line.length() - delimiterPosition - 1);
}

void Ini::loadFromFile(const std::string &filename) {
	std::map<std::string, IniSection> result;
	std::ifstream load(filename);
	
	if (!load.good()) {
		throw cfg::IniException("loadFromFile(...): Could not open file " + filename);
	}
	
	std::string line;
	std::string section = "root";
	std::string key, value;
	while (std::getline(load, line)) {
		if (isSectionHeader(line)) {
			getSectionIdentifier(line, section);
		}
		else if (isKeyValuePair(line)) {
			getKeyValue(line, key, value);
			result[section][key] = value;
		}
		else if (not line.empty()) {
			throw cfg::IniException("Ini::loadFromFile(...): Invalid line " + line);
		}
	}
	
	load.close();
	load.clear();

	config = result;
}

template<typename T>
std::vector<std::string> getSortedMapKeys(const std::map<std::string, T> &map) {
	std::vector<std::string> result;
	result.reserve(map.size());
	
	for (auto key : map) {
		result.push_back(key.first);
	}
	
	std::sort(result.begin(), result.end());
	
	return result;
}

void Ini::saveToFile(const std::string &filename) {
	std::ofstream save (filename);
	
	if (!save.good()) {
		throw cfg::IniException("Ini::saveToFile(...): Could not open file " + filename);
	}
	
	auto headerKeys = getSortedMapKeys(config);
	for (auto sortedKey : headerKeys) {
		save << "[" << sortedKey << "]\n";
		
		auto sectionKeys = getSortedMapKeys(config[sortedKey]);
		for (auto key : sectionKeys) {
			save << key << "=" << config[sortedKey][key].asString() << "\n";
		}
		
		save << "\n";
	}
	
	save.close();
	save.clear();
}