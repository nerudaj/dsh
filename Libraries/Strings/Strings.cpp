/**
 *  \file 			Strings.hpp
 *  \author			doomista
 */

#include <algorithm> 
#include <cctype>
#include <locale>
#include <algorithm>
#include <ciso646>
#include <bitset>
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

static inline void ltrim(std::string &s) {
    s.erase(s.begin(), std::find_if(s.begin(), s.end(), [](int ch) {
        return !std::isspace(ch);
    }));
}

// trim from end (in place)
static inline void rtrim(std::string &s) {
    s.erase(std::find_if(s.rbegin(), s.rend(), [](int ch) {
        return !std::isspace(ch);
    }).base(), s.end());
}

void Strings::trim(std::string &str) {
	ltrim(str);
	rtrim(str);
}

bool Strings::isPrefixOf(const std::string &str, const std::string &ofWhat) {
	if (str.size() > ofWhat.size()) return false;
	
	return std::equal(
		str.begin(),
		str.begin() + std::min( str.size(), ofWhat.size() ),
		ofWhat.begin()
	);
}

const char BASE64_LOOKUP_TABLE[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";

std::string Strings::encodeToBase64(const std::string &text) {
	std::string result = "";
	result.reserve(text.size() * 4 / 3);

	uint32_t buffer = 0, b = 0;
	for (uint8_t c : text) {
		buffer <<= 8;
		b += 8;
		buffer |= c;

		while (b >= 6) {
			b -= 6;
			result += BASE64_LOOKUP_TABLE[(buffer >> b) & 0x3f];
		}	
	}

	if (b > 0) { // last character not encoded + some padding is needed
		buffer <<= (6 - b);
		result += BASE64_LOOKUP_TABLE[buffer & 0x3f]; // encode last bits
		result += std::string((6 - b) / 2, '='); // add a padding
	}

	return result;
}

std::string Strings::decodeFromBase64(const std::string &encoded) {
	std::string result = "";

	auto getReverseLookup = [](char c) {
		const uint8_t minorOffset = ('Z' - 'A') + 1;
		const uint8_t numberOffset = 2 * minorOffset;
		if ('A' <= c && c <= 'Z') return uint8_t(c - 'A');
		else if ('a' <= c && c <= 'z') return uint8_t(c - 'a' + minorOffset);
		else if ('0' <= c && c <= '9') return uint8_t(c - '0' + numberOffset);
		else if (c == '+') return uint8_t(62);
		else if (c == '/') return uint8_t(63);
		throw std::runtime_error(c + " is an invalid character!");
	};

	uint32_t buffer = 0, b = 0;
	for (char c : encoded) {
		if (c == '=') break;
		uint8_t index = getReverseLookup(c);

		buffer <<= 6;
		b += 6;
		buffer |= index;

		while (b >= 8) {
			b -= 8;
			result += (buffer >> b) & 0xff;
		}
	}

	return result;
}