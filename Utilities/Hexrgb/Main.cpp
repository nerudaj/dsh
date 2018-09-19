#include <iostream>
#include <Config.hpp>
#include <ciso646>
#include <regex>
#include <cassert>

void printHelp(char *progname) {
	std::cout << "Usage:\n";
	std::cout << "\t" << progname << " [-h] hexavalue hexavalue ...\n";
	
	std::vector<std::pair<std::string, std::string>> rows = {
		{"-h", "Prints this text"},
		{"-s", "Scale values to represent percentage (255 is 100%)." },
	};
	
	for (auto row : rows) {
		std::cout << "\t" << row.first << ": " << row.second << "\n";
	}
	
	std::cout << "\n";
	std::cout << "Details: You can convert multiple hexavalues at once, each one of them will be printed to single line. Hexavalue can start with # symbol, it can have three or six symbols, it can use both minuscule and majuscule letters. Three letter values will be interpreted as following: #abc => #aabbcc.\n";
}

bool isHexvar(const std::string &var) {
	return std::regex_match(var, std::regex("[#]?([0-9a-fA-F]{3}){1,2}"));
}

int power (int base, int exp) {
	int result = 1;
	for (int i = 0; i < exp; i++) {
		result *= base;
	}
	return result;
}

int hexToInt(const char c) {
	if ('0' <= c && c <= '9') return int(c - '0');
	else if ('A' <= c && c <= 'F') return int(c - 'A') + 10;
	else if ('a' <= c && c <= 'f') return int(c - 'a') + 10;
	else {
		assert(false);
	}
}

void convertAndPrint(const std::string &var, bool scale) {
	std::string str = var;
	
	// Strip optional # symbol
	if (str[0] == '#') {
		str = str.substr(1, str.size() - 1);
	}
	
	// Compute and store values
	std::vector<int> rgb (3, 0);
	for (int i = 0; i < 3; i++) { // r = 0, g = 1, b = 2
		for (int e = 1; e >= 0; e--) {
			rgb[i] += power(16, e) * hexToInt(str[str.size() == 6 ? i * 2 + e : i]);
		}
	}
	
	// Scale to 0..100 if required
	if (scale) {
		for (auto &val : rgb) {
			val = 100 * val / 255;
		}
	}
	
	// Print
	std::cout << '#' << str << " = rgb(" << rgb[0] << ", " << rgb[1] << ", " << rgb[2] << ")\n";
}

int main(int argc, char *argv[]) {
	cfg::Args args;
	args.setupArguments("hs");
	
	if (not args.parse(argc, argv)) {
		printHelp(argv[0]);
		return 1;
	}
	
	bool scale = args.isSet('s');
	
	auto toConv = args.getPositionalArguments();
	if (toConv.size() == 0 || args.isSet('h')) {
		printHelp(argv[0]);
		return 0;
	}
	
	for (auto item : toConv) {
		if (isHexvar(item)) {
			convertAndPrint(item, scale);
		}
		else {
			std::cerr << "ERROR: " << item << " is not a valid hexa value\n";
		}
	}
	
	return 0;
}