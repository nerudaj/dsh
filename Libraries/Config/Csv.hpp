#pragma once

#include "Config.hpp"
#include <vector>

namespace cfg {
	class Csv {
	public:
		/**
		 *  \brief Load CSV file
		 *  
		 *  \param [in] filename Path to file
		 *  \param [in] pedantic Whether to engage pedantic mode
		 *  \param [in] delimiter Delimiter symbol (separates columns)
		 *  \param [in] newline Newline symbol (separates rows)
		 *  \param [in] quote Escape/Quote symbol
		 *  
		 *  If pedantic is set, then all rows of the loaded file need to have the
		 *  same number of columns, otherwise loading will fail with a CsvException
		 */
		static std::vector<std::vector<Item>> loadFromFile(const std::string &filename, bool pedantic = false, char delimiter = ',', char newline = '\n', char quote = '"');
		
		/**
		 *  \brief Exports CSV to file
		 *  
		 *  \param [in] filename Path to file
		 *  \param [in] delimiter Delimiter symbol (separates columns)
		 *  \param [in] newline Newline symbol (separates rows)
		 *  \param [in] quote Escape/quote symbol
		 *  
		 *  Any value that needs escaping (contains delimiter symbol, newline symbol or quote symbol) 
		 *  will be properly escaped and quoted.
		 */
		static void saveToFile(const std::vector<std::vector<Item>> &data, const std::string &filename, char delimiter = ',', char newline = '\n', char quote = '"');
	};
}
