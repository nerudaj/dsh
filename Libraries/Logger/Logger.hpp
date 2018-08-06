#ifndef LOGGER_HPP_
#define LOGGER_HPP_

#include <iostream>

class Logger {
public:
	static int loglevel;
	
	static void debug(const std::string &module, const std::string &message);
	static void info(const std::string &module, const std::string &message);
	static void warning(const std::string &module, const std::string &message);
	static void error(const std::string &module, const std::string &message);
};

#endif
