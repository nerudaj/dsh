#include "Args.hpp"
#include <regex>
#include <Logger.hpp>

using namespace cfg;

bool isValidArgArray(const std::string &str) {
	return std::regex_match (str, std::regex("([a-zA-Z]([\\!\\:])?)+"));
}

bool hasArgumentFormat(const std::string &str) {
	return std::regex_match (str, std::regex("-[a-zA-Z]"));
}

bool Args::isOptionDefined(const std::string &opt) {
	return arguments.find(opt) != arguments.end();
}

bool Args::parse(int argc, char *argv[]) {
	positionals.clear();
	
	// Parse arguments
	for (int i = 1; i < argc; i++) {
		std::string opt(argv[i]);
		
		Logger::debug("Args", "Parsing argument " + opt);
		
		// If it is '-[a-zA-Z]' string, treat it like a argument
		if (hasArgumentFormat(opt)) {
			if (not isOptionDefined(opt)) { // And check whether it is in arguments map
				Logger::error("Args", opt + " is an unknown argument");
				return false;
			}
		}
		else { // Otherwise treat it like positional argument
			positionals.push_back(opt);
			continue;
		}
		
		// Check if it is first occurence of the argument
		if (arguments[opt].set) {
			Logger::error("Args", opt + " is already set");
			return false;
		}
		arguments[opt].set = true;
		
		// Work out optional values
		if (arguments[opt].hasValue) {
			if (i + 1 >= argc) {
				Logger::error("Args", "Argument " + opt + " requires a value");
				return false;
			}
			
			i++;
			arguments[opt].value = std::string(argv[i]);
		}
	}
	
	// Check if all required are set
	for (auto argument : arguments) {
		if (argument.second.required and not argument.second.set) {
			Logger::error("Args", "Argument " + argument.first + " is mandatory");
			return false;
		}
	}
	
	return true;
}

bool Args::setupArguments(const std::string &argarray) {
	if (not isValidArgArray(argarray)) {
		Logger::error("Args", "Given argarray is not valid. It must compy to regex: ([a-zA-Z]([!:])?)+");
		return false;
	}
	
	for (unsigned i = 0; i < argarray.size(); i++) {
		std::string opt = "-";
		opt += argarray[i];
		
		Logger::debug("Args", "Dealing with argument " + opt);
		
		if (isOptionDefined(opt)) {
			Logger::error("Args", "Redefinition of argument " + opt);
			return false;
		}
		
		arguments[opt].set = false;
		
		if (i + 1 < argarray.size()) {
			char c = argarray[i + 1];
			
			if (c == '!') {
				Logger::debug("Args", "Argument is mandatory");
				arguments[opt].hasValue = true;
				arguments[opt].required = true;
				i++;
			}
			else if (c == ':') {
				Logger::debug("Args", "Argument has a value");
				arguments[opt].hasValue = true;
				i++;
			}
		}
	}
	
	return true;
}