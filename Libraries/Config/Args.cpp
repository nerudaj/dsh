#include "Args.hpp"
#include <regex>

using namespace cfg;

bool isValidArgArray(const std::string &str) {
	return std::regex_match (str, std::regex("([a-zA-Z]([\\:])?)+"));
}

bool hasArgumentFormat(const std::string &str) {
	return std::regex_match (str, std::regex("-[a-zA-Z]"));
}

bool Args::isOptionDefined(const std::string &opt) {
	return arguments.find(opt) != arguments.end();
}

void Args::parse(int argc, const char * const argv[]) {
	positionals.clear();

	// Parse arguments
	for (int i = 1; i < argc; i++) {
		std::string opt(argv[i]);

		// If it is '-[a-zA-Z]' string, treat it like a argument
		if (hasArgumentFormat(opt)) {
			if (not isOptionDefined(opt)) { // And check whether it is in arguments map
				throw ArgsException(opt + " is an unknown argument");
			}
		}
		else { // Otherwise treat it like positional argument
			positionals.push_back(opt);
			continue;
		}

		// Check if it is first occurence of the argument
		if (arguments[opt].set) {
			throw ArgsException(opt + " is already set");
		}
		arguments[opt].set = true;

		// Work out optional values
		if (arguments[opt].hasValue) {
			if (++i >= argc) {
				throw ArgsException("Argument " + opt + " requires a value");
			}

			arguments[opt].value = std::string(argv[i]);
		}
	}
}

void Args::setupArguments(const std::string &argarray) {
	if (not isValidArgArray(argarray)) {
		throw cfg::ArgsException("Given argarray is not valid. It must compy to regex: ([a-zA-Z]([:])?)+");
	}

	std::map<std::string, cfg::Arg> inArgs;

	for (unsigned i = 0; i < argarray.size(); i++) {
		std::string opt = "-";
		opt += argarray[i];

		if (isOptionDefined(opt)) {
			throw cfg::ArgsException("Redefinition of argument " + opt);
		}

		inArgs[opt].set = false;

		char c = argarray[i + 1];

		if (c == ':') {
			inArgs[opt].hasValue = true;
			i++;
		}
	}

	arguments = inArgs;
}

const cfg::Item &Args::getArgumentValue(const char argument) const {
	std::string arg = "-";
	arg += argument;

	if (not isSet(argument)) throw ArgsException("-" + std::string(arg) + " is not set!");

	return arguments.at(arg).value;
}