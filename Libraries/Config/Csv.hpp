#ifndef CFG_CSV_HPP_
#define CFG_CSV_HPP_

#include "Config.hpp"
#include <vector>
#include <Logger.hpp>

namespace cfg {
	class Csv {
	protected:
		std::vector<std::vector<cfg::Item>> rows;
		std::vector<cfg::Item>headers;
	
		bool parseLine(char **buffer, std::vector<cfg::Item> &row, int flags, char delimiter, char newline, char quote);
		void tokenToRow(const char *buffer, int start, int last, std::vector<cfg::Item> &row, char quote);
		Logger log;
	
	public:
		enum Flags { None = 0, Pedantic = 1, NoHeaders = 2 };
	
		bool loadFromFile(const std::string &filename, int flags, char delimiter = ',', char newline = '\n', char quote = '"') noexcept;
		
		bool saveToFile(const std::string &filename, char delimiter = ',', char newline = '\n', char quote = '"');
		
		void setHeaders(const std::vector<cfg::Item> &headers);
		
		const std::vector<cfg::Item> &getHeaders() const { return headers; }
		
		unsigned getSize() const { return rows.size(); }
		
		// Overloading
		const std::vector<cfg::Item> &operator[](unsigned i) const { return rows[i]; }
		
		std::vector<cfg::Item> &operator[](unsigned i) { return rows[i]; }
		
		std::vector<std::vector<cfg::Item>>::iterator begin() noexcept { return rows.begin(); }
		
		const std::vector<std::vector<cfg::Item>>::const_iterator begin() const noexcept { return rows.begin(); }
		
		std::vector<std::vector<cfg::Item>>::iterator end() noexcept { return rows.end(); }
		
		const std::vector<std::vector<cfg::Item>>::const_iterator end() const noexcept { return rows.end(); }
		
		Csv();
	};
}

#endif
