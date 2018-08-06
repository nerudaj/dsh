#include "Args.hpp"
#include <regex>
#include <Logger.hpp>

using namespace cfg;

bool isValidArgArray(const std::string &str) {
	return std::regex_match (str, std::regex("([a-zA-Z]([\\!\\:])?)+"));
}

bool Args::isOptionDefined(const std::string &opt) {
	return arguments.find(opt) != arguments.end();
}

bool Args::parse(int argc, char *argv[]) {
	// Parse arguments
	for (int i = 0; i < argc; i++) {
		std::string opt(argv[i]);
		
		// TODO: Positional argument
		if (not isOptionDefined(opt)) {
			Logger::error("Args", opt + " is an unknown argument");
			return false;
		}
		
		arguments[opt].set = true;
		
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
		std::string opt = "-" + argarray[i];
		
		if (isOptionDefined(opt)) {
			Logger::error("Args", "Redefinition of argument " + opt);
			return false;
		}
		
		arguments[opt].set = false;
		
		if (i + 1 < argarray.size()) {
			char c = argarray[i + 1];
			
			if (c == '!') {
				arguments[opt].hasValue = true;
				arguments[opt].required = true;
				i++;
			}
			else if (c == ':') {
				arguments[opt].hasValue = true;
				i++;
			}
		}
	}
	
	return true;
}