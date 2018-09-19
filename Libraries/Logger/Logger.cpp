#include "Logger.hpp"

void Logger::debug(const std::string &module, const std::string &message) {
	if (loglevel >= 4) {
		std::cout << "DEBUG: " << module << ": " << message << std::endl;
	}
}

void Logger::info(const std::string &module, const std::string &message) {
	if (loglevel >= 3) {
		std::cout << "INFO: " << module << ": " << message << std::endl;
	}
}

void Logger::warning(const std::string &module, const std::string &message) {
	if (loglevel >= 2) {
		std::cerr << "WARNING: " << module << ": " << message << std::endl;
	}
}

void Logger::error(const std::string &module, const std::string &message) {
	if (loglevel >= 1) {
		std::cerr << "ERROR: " << module << ": " << message << std::endl;
	}
}

void Logger::setLoggingLevel(int level) {
	loglevel = level;
}

Logger::Logger() {
	loglevel = 1;
}