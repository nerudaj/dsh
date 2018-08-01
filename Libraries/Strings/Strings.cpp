/**
 *  \file 			Strings.hpp
 *  \author			doomista
 */

#include "Strings.hpp"

using std::size_t;

void Strings::split(const char delimiter, const std::string &src, std::vector<std::string> &dst) {
	if (not dst.empty()) dst.clear(); // Make sure destination vector is empty
	
	std::size_t pos = 0; // Index of start of each substring
	bool multidelim = true; // We need to handle multiple delimiters one after each other
	
	for (std::size_t i = 0; i < src.size(); i++) { // Loop over all characters in string
		if (src[i] == delimiter) { // If delimiter is found
			if (!multidelim) { // And is not just one of many
				dst.push_back(src.substr(pos, i - pos)); // Push new substring to dst
				pos = i + 1; // New substring may start here
				multidelim = true; // Or this might be first of many delimiters
			}
			else { // If delimiter is just one of many
				pos++; // Start of new substring may be over there
			}
		}
		else { // If current character is anything other than delimiter, turn off multidelim
			multidelim = false;
		}
	}
	
	if (pos < src.size()) { // There might be trailing substring
		dst.push_back(src.substr(pos, src.size() - pos)); // Add it
	}
}

void Strings::replaceAll(std::string &str, const std::string &from, const std::string &to) {
	if(from.empty()) return;
	
	size_t start_pos = 0;
	while((start_pos = str.find(from, start_pos)) != std::string::npos) {
		str.replace(start_pos, from.length(), to);
		start_pos += to.length(); // In case 'to' contains 'from', like replacing 'x' with 'yx'
	}
}