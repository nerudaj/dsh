#include <fstream>
#include <iostream>
#include <string>
#include <Strings.hpp>
#include "Csv.hpp"

using cfg::Csv;
using cfg::Item;

enum class ParserMode {
	Start,
	Quoted,
	Unquoted,
	Endquote
};

struct ParserSettings {
	char delimiter;
	char quote;
	char newline;
};

bool parseToken(const std::string &file, std::string::const_iterator &itr, std::string &token, ParserSettings settings) {
	ParserMode mode = ParserMode::Start;

	auto first = itr;
	auto last = itr;
	bool parsing = true, rtncode = true;

	while (parsing) {
		if (itr == file.end()) {
			last = itr;
			rtncode = false;
			break;
		}
		
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
			if (*itr == settings.quote) {
				 mode = ParserMode::Endquote;
			}
			break;

		case ParserMode::Unquoted:
			if (*itr == settings.delimiter) {
				last = itr;
				parsing = false;
			}
			else if (*itr == settings.newline) {
				last = itr;
				parsing = false;
				rtncode = false;
			}
			else if (*itr == settings.quote) {
				throw cfg::CsvException("Invalid '" + std::string(1, settings.quote) + "' character at position: " + std::to_string(itr - file.begin()));
			}
			break;
			
		case ParserMode::Endquote:
			if (*itr == settings.delimiter) {
				last = itr;
				parsing = false;
			}
			else if (*itr == settings.newline) {
				last = itr;
				parsing = false;
				rtncode = false;
			}
			else if (*itr == settings.quote) {
				mode = ParserMode::Quoted;
			}
			else {
				throw cfg::CsvException("Invalid non-delimiter, non-newline character followed after closing quote at position: " + std::to_string(itr - file.begin()));
			}
			break;
		}
		
		itr++;
	}
	
	token = std::string(first, last);
	
	return rtncode;
}

bool parseLine(const std::string &file, std::string::const_iterator &itr, std::vector<cfg::Item> &row, ParserSettings settings) {
	if (itr == file.end()) return false; // Parsing ended

	row.clear();

	std::string token;

	// Read tokens until line end
	bool rtn;
	do {
		rtn = parseToken(file, itr, token, settings);
		
		if (token[0] == token.back() && token[0] == settings.quote) {
			token = token.substr(1, token.size() - 2);
			Strings::replaceAll(token, std::string(1, settings.quote) + std::string(1, settings.quote), std::string(1, settings.quote));
		}
		
		row.push_back(cfg::Item(token));
	} while (rtn);

	return true;
}

std::vector<std::vector<Item>> Csv::loadFromFile(const std::string &filename, bool pedantic, char delimiter, char newline, char quote) {
	std::vector<std::vector<Item>> result;
	std::string file;
	
	// Load file into memory
	try {
		std::ifstream load(filename);

		// Get size of file
		load.seekg(0, load.end);
		unsigned fsize = load.tellg();
		load.seekg(0, load.beg);

		// Allocate buffer
		char *filebuf = new char[fsize];
		if (filebuf == NULL) {
			throw CsvException("loadFromFile: memory allocation failed");
		}

		// Read file into memory
		load.read(filebuf, fsize);
		file = std::string(filebuf, fsize);
		delete[] filebuf;

		load.close();
		load.clear();
	} catch (std::exception &e) {
		throw CsvException("loadFromFile: error when loading file to memory: " + std::string(e.what()));
	}
	
	std::string::const_iterator fileItr = file.begin();
	std::vector<Item> row;

	// Parse file, line by line
	while (parseLine(file, fileItr, row, {delimiter, quote, newline})) {
		if (pedantic && not result.empty()) {
			if (row.size() != result.begin()->size()) {
				throw CsvException("loadFromFile: Rows do not have the same number of columns and pedantic flag has been set");
			}
		}

		try {
			result.push_back(row);
		} catch (std::exception &e) {
			throw CsvException("loadFromFile: memory allocation failed: " + std::string(e.what()));
		}
	}
	
	return result;
}

void writeVectorOfCsvItems(std::ofstream &save, std::vector<cfg::Item> &row, char delimiter, char newline, char quote) {
	for (unsigned i = 0; i < row.size(); i++) {
		bool doQuote = false;
		std::string toWrite = row[i].asString();

		// Turn quotes to double quotes
		if (toWrite.find(quote) != std::string::npos) {
			doQuote = true;
			Strings::replaceAll(toWrite, std::string(1, quote), std::string(1, quote) + std::string(1, quote));
		}

		doQuote |= (toWrite.find(delimiter) != std::string::npos);
		doQuote |= (toWrite.find(newline) != std::string::npos);

		if (doQuote) {
			toWrite = std::string(1, quote) + toWrite + std::string(1, quote);
		}

		save << toWrite;
		if (i < row.size() - 1) save << delimiter;
	}

	save << newline;
}

void Csv::saveToFile(const std::vector<std::vector<Item>> &data, const std::string &filename, char delimiter, char newline, char quote) {
	try {
		std::ofstream save (filename);

		for (auto row : data) {
			writeVectorOfCsvItems(save, row, delimiter, newline, quote);
		}

		save.close();
		save.clear();
	}
	catch (std::exception &e) {
		throw CsvException("saveToFIle: error: " + std::string(e.what()));
	}
}