#include <fstream>
#include <string>
#include <Strings.hpp>
#include "Csv.hpp"

using cfg::Csv;

enum class ParserMode {
	Start,
	Quoted,
	Unquoted
};

struct ParserSettings {
	char delimiter;
	char quote;
	char newline;
}

bool parseToken(const std::string &file, std::string::const_iterator &itr, std::string &token, int flags, ParserSettings settings) {
	ParserMode mode = ParserMode::Start;

	std::string token;

	while (true) {
		switch (mode) {
		case ParserMode::Start:
			if (*itr == settings.quote) {
				mode = ParserMode::Quoted;
			}
			else {
				mode = ParserMode::Unquoted;
			}
			break;
			
		case ParserMode::Quoted:
			
			break;

		case ParserMode::Unquoted:
			break;
		}
	}
	
	return true;
}

bool Csv::parseLine(const std::string &file, std::string::const_iterator &itr, std::vector<cfg::Item> &row, int flags, ParserSettings settings) {
	if (itr == file.end()) return false; // Parsing ended

	row.clear();

	std::string token;

	// Read tokens until line end
	while (parseToken(file, itr, token, flags, settings)) {
		if (token[0] == token.back() && token[0] == settings.quote) {
			token = token.substr(1, token.size() - 2);
			Strings::replaceAll(token, std::string(settings.quote) + std::string(settings.quote), std::string(settings.quote);
		}
		
		row.push_back(cfg::Item(token));
	}

	return true;
}

bool Csv::loadFromFile(const std::string &filename, int flags, char delimiter, char newline, char quote) noexcept {
	std::string file;
	std::vector<cfg::Item> row;

	// Load file into memory
	try {
		std::ifstream load(filename);

		// Get size of file
		load.seekg(0, load.end);
		unsigned fsize = load.tellg();
		load.seekg(0, load.begin);

		// Allocate buffer
		char *filebuf = new char[fsize];
		if (filebuf == NULL) throw std::bad_alloc;

		// Read file into memory
		load.read(filebuf, fsize);
		file = std::string(filebuf, fsize);

		load.close();
		load.clear();
	}
	catch (std::exception &e) {
		log.error("Csv::loadFromFile", "Exception: " + std::string(e.what()));
		return false;
	}
	
	// Parse file
	auto fileItr = file.begin();
	
	// Process headers
	if (!(flags & Csv::Flags::NoHeaders)) {
		parseLine(file, fileItr, row, flags, {delimiter, quote, newline});
		headers = row;
	}
	
	// Process body
	while (parseLine(file, fileItr, row, flags, {delimiter, quote, newline})) {
		rows.push_back(row);
	}
	
	return true;
}

bool Csv::saveToFile(const std::string &filename, char delimiter, char newline, char quote) {
	try {
		log.error("Csv::saveToFile", "Not implemented");
		return false;
	}
	catch (std::exception &e) {
		log.error("Csv::saveToFile", "Exception: " + std::string(e.what()));
		return false;
	}
	
	return true;
}

std::size_t Csv::headerID(const std::string &name) {
	for (std::size_t i = 0; i < headers.size(); i++) {
		if (headers[i].asStr() == name) {
			return i;
		}
	}
	
	throw std::out_of_range;
	return -1; // Never happens
}

void Csv::setHeaders(const std::vector<cfg::Item> &headers) {
	log.info("Csv::setHeaders", "TODO this");
	Csv::headers = headers;
}

Csv::Csv() {
	log.setLoggingLevel(4);
}