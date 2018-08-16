#ifndef LOGGER_HPP_
#define LOGGER_HPP_

#include <iostream>

/**
 *  \brief Simple class for logging events
 *  
 *  \details Logs are produced based on the set loglevel (default: 1)
 */
class Logger {
private:
	static unsigned loglevel; ///< Level determining which events will be reported. Default: 1. Logs nothing if set to 0

public:
	/**
	 *  \brief Logs a debug message
	 *  
	 *  \param [in] module Module from where the message originates
	 *  \param [in] message Message itself
	 *  
	 *  \details Logging happen if the loglevel is 4 or higher. Newline is appended to message. Log format:
	 *  DEBUG: <module>: <message>
	 */
	static void debug(const std::string &module, const std::string &message);
	
	/**
	 *  \brief Logs an info message
	 *  
	 *  \param [in] module Module from where the message originates
	 *  \param [in] message Message itself
	 *  
	 *  \details Logging happen if the loglevel is 3 or higher. Newline is appended to message. Log format:
	 *  INFO: <module>: <message>
	 */
	static void info(const std::string &module, const std::string &message);
	
	/**
	 *  \brief Logs a warning message
	 *  
	 *  \param [in] module Module from where the message originates
	 *  \param [in] message Message itself
	 *  
	 *  \details Logging happen if the loglevel is 2 or higher. Newline is appended to message. Log format:
	 *  WARNING: <module>: <message>
	 */
	static void warning(const std::string &module, const std::string &message);
	
	/**
	 *  \brief Logs an error message
	 *  
	 *  \param [in] module Module from where the message originates
	 *  \param [in] message Message itself
	 *  
	 *  \details Logging happen if the loglevel is 1 or higher. Newline is appended to message. Log format:
	 *  ERROR: <module>: <message>
	 */
	static void error(const std::string &module, const std::string &message);
};

#endif
