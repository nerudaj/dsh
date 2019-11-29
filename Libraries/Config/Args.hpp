#pragma once

#include <iostream>
#include <map>
#include <vector>

#include "Config.hpp"

namespace cfg {
	/**
	 *  \brief Auxiliary struct for handling argument parsing
	 */
	struct Arg {
		cfg::Item value; ///< Value of the argument (if there is one)
		
		bool required; ///< Is the argument mandatory?
		bool hasValue; ///< Has the argument value (always yes if it is required)
		bool set; ///< Has it been set? (set during parsing)
	};
	
	/**
	 *  \brief Class for parsing command line arguments
	 *  
	 *  \details Only supports short arguments and no argument grouping.
	 *  Arguments can be mandatory and can have values. There also can be
	 *  positional arguments as well. These are always accepted by default.
	 */
	class Args {
	protected:
		std::map<std::string, cfg::Arg> arguments; ///< Parsed arguments
		std::vector<std::string> positionals; ///< Positional arguments

		/**
		 *  \brief Is option defined in arguments array
		 *  
		 *  \param [in] opt Option in form '-L' where L is any alphabetical letter
		 *  \return TRUE if is
		 */
		bool isOptionDefined(const std::string &opt); ///< Whether option is stored in arguments
		
	public:
		/**
		 *  \brief Parse command line arguments
		 *  
		 *  \param [in] argc Argument count
		 *  \param [in] argv Arguments
		 *  \return TRUE if parse was successful
		 *  
		 *  \pre \ref setupArguments was called
		 *  
		 *  \details Positional arguments are by default stored, no questions asked and
		 *  you can retrieve them with \ref getOtherArguments. Only exceptions
		 *  are arguments that have a format '-L' which are treated as regular
		 *  arguments and are checked against setup rules.
		 */
		void parse(int argc, const char * const argv[]);
		
		/**
		 *  \brief Setup how arguments will be parsed
		 *  
		 *  \param [in] argarray String with parsing instructions
		 *  \return TRUE if setup succeeded
		 *  
		 *  \details \p argarray has following format: It can
		 *  contain any number of nonrepeating alphabetical letters
		 *  (both minuscule and capital) and each of these letters
		 *  can be followed by one of the two special symbols ':' or '!'.
		 *  ':' means that argument has a value, '!' means that argument
		 *  is mandatory AND have a value.
		 *  
		 *  For example following \p argarray "hg:i!" means:
		 *  program [-h] [-g <value>] <-i <value>> where [] denotes optional
		 *  items and <> denotes mandatory items.
		 */
		void setupArguments(const std::string &argarray);
		
		/**
		 *  \brief Test if an argument was set during parsing
		 *  
		 *  \param [in] argument Single letter identifying the argument
		 *  \return TRUE if is set, FALSE otherwise
		 *  
		 *  \pre \ref parse was called
		 *  
		 *  \details If the \p argument is mandatory, then this check is not
		 *  needed, as long as \ref parse returned TRUE. Use this check prior
		 *  to calling \ref getArgumentValue on optional arguments.
		 */
		bool isSet(const char argument) const {
			std::string arg = "-";
			arg += argument;
			
			if (arguments.find(arg) == arguments.end()) return false;
			
			return arguments.at(arg).set;
		}
		
		/**
		 *  \brief Get value of a argument
		 *  
		 *  \param [in] argument Single letter identifying the argument
		 *  \return Reference to structure holding the argument value
		 *  
		 *  \details Since the reference is returned, always call \ref isSet
		 *  on optional arguments to prevent exceptions from being thrown.
		 */
		const cfg::Item &getArgumentValue(const char argument) const;
		
		/**
		 *  \brief Get parsed positional arguments
		 *  
		 *  \pre \ref parse was called
		 */
		const std::vector<std::string> &getPositionalArguments() const { return positionals; }

		Args() {}
		Args(const std::string &argarray) {
			setupArguments(argarray);
		}
	};
}
