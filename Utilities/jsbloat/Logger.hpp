#pragma once

#include <iostream>

class Logger {
public:
	void error(const std::string &module, const std::string &msg) {
		std::cerr << "ERROR: " << module << ": " << msg << std::endl;
	}

	void warning(const std::string &module, const std::string &msg) {
		std::cerr << "WARNING: " << module << ": " << msg << std::endl;
	}

	void info(const std::string &module, const std::string &msg) {
		std::cout << "INFO: " << module << ": " << msg << std::endl;
	}

	void debug(const std::string &module, const std::string &msg) {
		std::cout << "DEBUG: " << module << ": " << msg << std::endl;
	}

	void setLoggingLevel(int i) {}
};

extern Logger logger;