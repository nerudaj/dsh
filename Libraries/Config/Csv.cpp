#include <fstream>
#include <string>
#include <Strings.hpp>
#include "Csv.hpp"

using cfg::Csv;

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

bool parseToken(const std::string &file, std::string::const_iterator &itr, std::string &token, int flags, ParserSettings settings) {
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
				throw std::runtime_error("Invalid '" + std::string(1, settings.quote) + "' character at position: " + std::to_string(itr - file.begin()));
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
				throw std::runtime_error("Invalid non-delimiter, non-newline character followed after closing quote at position: " + std::to_string(itr - file.begin()));
			}
			break;
		}
		
		itr++;
	}
	
	token = std::string(first, last);
	
	return rtncode;
}

bool parseLine(const std::string &file, std::string::const_iterator &itr, std::vector<cfg::Item> &row, int flags, ParserSettings settings) {
	if (itr == file.end()) return false; // Parsing ended

	row.clear();

	std::string token;

	// Read tokens until line end
	bool rtn;
	do {
		rtn = parseToken(file, itr, token, flags, settings);
		
		if (token[0] == token.back() && token[0] == settings.quote) {
			token = token.substr(1, token.size() - 2);
			Strings::replaceAll(token, std::string(1, settings.quote) + std::string(1, settings.quote), std::string(1, settings.quote));
		}
		
		row.push_back(cfg::Item(token));
	} while (rtn);

	return true;
}

bool Csv::loadFromFile(const std::string &filename, int flags, char delimiter, char newline, char quote) noexcept {
	std::string file;
	std::vector<cfg::Item> row;

	if (flags & int(Flags::ResetHeaders)) {
		headers.clear();
	}
	
	// Load file into memory
	try {
		std::ifstream load(filename);

		// Get size of file
		load.seekg(0, load.end);
		unsigned fsize = load.tellg();
		load.seekg(0, load.beg);

		log.debug("Csv::loadFromFile", "File size is " + std::to_string(fsize) + " bytes.");

		// Allocate buffer
		char *filebuf = new char[fsize];
		if (filebuf == NULL) throw std::bad_alloc();

		// Read file into memory
		load.read(filebuf, fsize);
		file = std::string(filebuf, fsize);
		delete[] filebuf;

		load.close();
		load.clear();
	}
	catch (std::exception &e) {
		log.error("Csv::loadFromFile", "Exception: " + std::string(e.what()));
		return false;
	}
	
	// Parse file
	std::string::const_iterator fileItr = file.begin();
	
	// Process headers
	if (!(flags & std::size_t(Csv::Flags::NoHeaders))) {
		parseLine(file, fileItr, row, flags, {delimiter, quote, newline});
		headers = row;
	}
	
	// Process body
	while (parseLine(file, fileItr, row, flags, {delimiter, quote, newline})) {
		if (!rows.empty() && !(flags & int(Flags::NoRowFit))) {
			std::size_t columnCount = headers.empty() ? rows[0].size() : headers.size();
			
			if (columnCount != row.size()) {
				log.debug("Csv::loadFromFile", "Row has bad number of rows. Adjusting...");
				
				if (flags & int(Flags::Pedantic)) {
					log.error("Csv::loadFromFile", "Row " + std::to_string(rows.size() - 1) + " does not have exactly " + std::to_string(columnCount) + " columns");
					return false;
				}

				// If we are not pedantic, adjust row size to fit
				while (columnCount > row.size()) row.push_back(Item());
				while (columnCount < row.size()) row.pop_back();
			}
		}

		rows.push_back(row);
	}
	
	return true;
}

/*bool Csv::saveToFile(const std::string &filename, char delimiter, char newline, char quote) {
	try {
		log.error("Csv::saveToFile", "Not implemented");
		return false;
	}
	catch (std::exception &e) {
		log.error("Csv::saveToFile", "Exception: " + std::string(e.what()));
		return false;
	}
	
	return true;
}*/

std::size_t Csv::headerID(const std::string &name) {
	for (std::size_t i = 0; i < headers.size(); i++) {
		if (headers[i].asString() == name) {
			return i;
		}
	}
	
	throw std::out_of_range("Header " + name + " is not available");
	return -1; // Never happens
}

void Csv::setHeaders(const std::vector<cfg::Item> &headers) {
	log.info("Csv::setHeaders", "TODO this");
	Csv::headers = headers;
}

Csv::Csv() {
	log.setLoggingLevel(3);
}