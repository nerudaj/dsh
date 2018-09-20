#include <fstream>
#include <string>
#include <Strings.hpp>
#include "Csv.hpp"

using cfg::Csv;

enum State { Word, Quote, TestDQuote };

#define EOFc std::char_traits<char>::eof()

class ParserException : public std::exception {
	virtual const char *what() const noexcept override {
		return "Unknown parser exception";
	}
};

class ParserExceptionEof : public ParserException {
	virtual const char *what() const noexcept final override {
		return "EOF was already encountered during parsing";
	}
};

bool Csv::parseLine(char **buffer, std::vector<cfg::Item> &row, int flags, char delimiter, char newline, char quote) {
	// Test eof, throw except if needed
	if ((*buffer)[0] == EOFc) throw ParserExceptionEof;

	row.clear();

	std::string token;
	int start = 0, last = 0;
	State state = State::Word;
	char c;
	// Read tokens until line end
	while (true) {
		c = *buffer[last];
		switch(state) {
		case State::Word:
			if (c == delimiter) {
				tokenToRow(*buffer, start, last, row, quote);
				start = last + 1;
			}
			else if (c == newline) {
				tokenToRow(*buffer, start, last, row, quote);

				// Last token on line, exit
				return (*buffer)[last + 1] != EOFc;
			}
			else if (c == quote) {
				state = State::Quote;
			}
			else if (c == EOFc) {
				tokenToRow(*buffer, start, last, row, quote);
				return false; // No data after this
			}
			break;

		case State::Quote:
			if (c == quote) {
				state = State::TestDQuote;
			}
			break;

		case State::TestDQuote:
			if (c == quote) {
				state = State::Quote;
			}
			else {
				last--;
				state = State::Word;
			}
			break;
		}

		last++;
	}

	return false;
}

void Csv::tokenToRow(const char *buffer, int start, int last, std::vector<cfg::Item> &row, char quote) {
	std::string token;
	// Copy buffer substr to token
	for (int i = start; i < last; i++) {
		token += (*buffer)[i];
	}
	
	// Remove start/end quotes
	if (token[0] == quote && token[token.size() - 1] == quote) {
		token = token.substr(1, token.size() - 2);
	}
	
	// Reduce doublequotes to single quotes
	//Strings::replaceAll(token, std::string(quote) + std::string(quote), std::string(quote));
	
	// Push it to row
	log.debug("Csv::parseLine", "Deparsed token is: " + token);
	row.push_back(cfg::Item());
	row.back() = token;
	token.clear();
}

bool Csv::loadFromFile(const std::string &filename, int flags, char delimiter, char newline, char quote) noexcept {
	try {
		std::ifstream load(filename);
		
		// Buffer
		std::vector<cfg::Item> row;
		char* filebuf;
		
		// Get size of file
		load.seekg(0, load.end);
		unsigned fsize = load.tellg();
		load.seekg(0, load.begin);
		
		// Create buffer and read file into memory
		filebuf = new char[fsize + 1];
		if (filebuf == NULL) throw std::bad_alloc;
		load.read(filebuf, fsize);
		filebuf[fsize] = char_traits<char>::eof();
		
		char *backup = filebuf;
		
		// Process headers
		if (!(flags & Csv::Flags::NoHeaders)) {
			parseLine(&filebuf, row, flags, delimiter, newline, quote);
			headers = row;
		}
		
		// Process body
		while (parseLine(&filebuf, row, flags, delimiter, newline, quote)) {
			rows.push_back(row);
		}
		
		free(backup); // filebuf is moved
		
		load.close();
		load.clear();
	}
	catch (std::exception &e) {
		log.error("Csv::loadFromFile", "Exception: " + std::string(e.what()));
		return false;
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