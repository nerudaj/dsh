#ifndef ARGS_HPP_
#define ARGS_HPP_

#include <iostream>
#include <map>
#include <vector>

#include "Item.hpp"

namespace cfg {
	struct Arg {
		cfg::Item value;
		
		bool required;
		bool hasValue;
		bool set;
	};
	
	class Args {
	protected:
		std::map<std::string, cfg::Arg> arguments;

		bool isOptionDefined(const std::string &opt);
		
	public:
		bool parse(int argc, char *argv[]);
		
		bool setupArguments(const std::string &argarray);
		
		bool isSet(const char argument) const {
			std::string arg = "-" + argument;
			return arguments.find(arg) != arguments.end();
		}
		
		const cfg::Item &getArgument(const char argument) const {
			std::string arg = "-" + argument;
			return arguments.at(arg).value;
		}
		
		//const std::vector<std::string> &getOtherArguments() const { return otherArguments; }
	};
}

#endif
