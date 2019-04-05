/**
 *  \file 			Strings.hpp
 *  \author			doomista
 *  \description	std::string manipulation helper methods
 */

#ifndef STRINGS_HPP_
#define STRINGS_HPP_

#include <vector>
#include <iostream>

class Strings {
public:
	/**
	 *  \brief Splits the string src by delimiter and stores resulting array of strings to dst
	 *  
	 *  \details dst is always cleared at the start of the function. Multiple delimiters one
	 *  after each other are treated as one.
	 */
	static std::vector<std::string> split(const char delimiter, const std::string &src);
	
	static void split(const char delimiter, const std::string &src, std::vector<std::string> &dst);
	
	/**
	 *  \brief Replaces all occurences of from with to in str
	 */
	static void replaceAll(std::string &str, const std::string &from, const std::string &in);
	
	static std::string replaceAllCopy(std::string str, const std::string &from, const std::string &to) {
		replaceAll(str, from, to);
		return str;
	}
	
	static void trim(std::string &str);
	
	static std::string trimCopy(std::string str) {
		trim(str);
		return str;
	}

	static bool isPrefixOf(const std::string &str, const std::string &ofWhat);
};

#endif
