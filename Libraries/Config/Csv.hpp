#pragma once

#include "Config.hpp"
#include <vector>
#include <Logger.hpp>

namespace cfg {
	/**
	 *  \brief Simple module for loading, editing and saving CSV files
	 */
	class Csv {
	protected:
		std::vector<std::vector<cfg::Item>> rows; ///< Database of rows
		std::vector<cfg::Item>headers; ///< Array of headers (can be empty)

		Logger log;

	public:
		/**
		 *  \brief Flags for altering behaviour of \ref loadFromFile.
		 */
		enum class Flags : std::size_t {
			None = 0,
			Pedantic = 1,
			NoHeaders = 2,
			NoRowFit = 4,
			ResetHeaders = 8
		};

		/**
		 *  \brief Load CSV file
		 *  
		 *  \param [in] filename Path to file
		 *  \param [in] flags Modifiers for parser
		 *  \param [in] delimiter Delimiter symbol (separates columns)
		 *  \param [in] quote Escape/Quote symbol
		 *  \return TRUE if load succeeded, FALSE otherwise
		 *  
		 *  \details By default, first line of the file is considered 'header' line and items
		 *  on that line are not considered as values, but as headers. You can disable this with
		 *  'NoHeaders' flag. You can always set your own set of headers by hand.
		 *  
		 *  By default if any row has more/less items than first row, it is expanded/cropped to
		 *  match. By using 'Pedantic' flag this will not happen and loading will fail with error. By using 'NoRowFit' original values will be preserved with no error. Also, NoRowFit will surpress Pedantic.
		 *  Please do not use headerID in that case.
		 *  
		 *  'ResetHeaders' will clear any previously load headers.
		 */
		bool loadFromFile(const std::string &filename, int flags, char delimiter = ',', char newline = '\n', char quote = '"') noexcept;
		
		/**
		 *  \brief Exports CSV to file
		 *  
		 *  \param [in] filename Path to file
		 *  \param [in] delimiter Delimiter symbol (separates columns)
		 *  \param [in] quote Escape/quote symbol
		 *  \return TRUE if save succeeded, FALSE otherwise
		 *  
		 *  \details If any headers were set, they are automatically exported as well. Any value that needs escaping (contains delimiter symbol, newline symbol or quote symbol) will be properly escaped and quoted.
		 */
		bool saveToFile(const std::string &filename, char delimiter = ',', char newline = '\n', char quote = '"');
		
		/**
		 *  \brief Set new array of headers
		 *  
		 *  \param [in] headers Array of headers
		 *  
		 *  \details If you set headers manually prior to loading, you can use them for row
		 *  length correction and error detection.
		 */
		void setHeaders(const std::vector<cfg::Item> &headers);
		
		/**
		 *  \brief Get index of column with \p name header value
		 *  
		 *  \param [in] name Value of the header
		 *  \return Index of header. If no header with that name is present, exception std::out_of_range is thrown.
		 */
		std::size_t headerID(const std::string &name);
		
		/**
		 *  \brief Get array of headers
		 *  
		 *  \return Array of headers. Array might be empty if no headers were parsed out of file
		 *  and/or set.
		 */
		const std::vector<cfg::Item> &getHeaders() const { return headers; }
		
		/**
		 *  \brief Get number of rows currently stored in object
		 *  
		 *  \return Number of rows. 0 if nothing is loaded.
		 */
		unsigned size() const { return rows.size(); }
		
		/**
		 *  \brief Resize CSV database
		 *  
		 *  \param [in] rowCount New number of rows
		 *  \param [in] colCount New number of columns (default: 0)
		 *  
		 *  \details This function will change number of rows (and 
		 *  possibly columns) in csv database. If rowCount is bigger
		 *  than current size, old rows are left unchanged and new 
		 *  rows are added.
		 *  
		 *  If colCount is not zero, new rows will be resized to 
		 *  accomodate that many columns.
		 */
		void resize(unsigned rowCount, unsigned colCount = 0);
		
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
