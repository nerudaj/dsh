#pragma once

#include "Item.hpp"
#include "Ini.hpp"
#include "Args.hpp"
#include "Csv.hpp"
#include <stdexcept>

namespace cfg {
    /**
     * \brief A parent exception class for errors related to cfg namespace
     */
    class Exception : public std::runtime_error {
    public:
        Exception(const std::string &message) : std::runtime_error(message) {}
    };

    class ArgsException : public Exception {
    public:
		ArgsException(const std::string &message) : Exception(message) {}
    };

    class IniException : public Exception {
    public:
		IniException(const std::string &message) : Exception(message) {}
    };

    /**
	 * \brief An exception for Csv related errors
	 */
	class CsvException : public Exception {
	public:
		CsvException(const std::string &message) : Exception(message) {}
	};
}