/**
 *  \file Ini.hpp
 *  
 *  \author Jakub Neruda
 *  
 *  \brief Class for parsing INI files
 */

#pragma once

#include "Config.hpp"
#include <Logger.hpp>
#include <map>

namespace cfg {
	/**
	 *  \brief Section of an ini file
	 */
	class IniSection : public std::map<std::string, Item> {
	public:
		/**
		 *  \brief Test whether key is present in section
		 *  
		 *  \param [in] key Key to test
		 *  \return TRUE if key is present in section
		 */
		bool hasKey(const std::string &key) const { return find(key) != end(); }
		
		IniSection() {}
		IniSection(const std::map<std::string, Item> &map) : std::map<std::string, Item>(map) {}
	};

	/**
	 *  \brief Simple class for loading and exporting ini files
	 *  
	 *  \details An ini file looks like this:
	 *  key=value
	 *  
	 *  [section]
	 *  key2=value2
	 *  
	 *  You can have any number of key=value lines and section headers. Every key=value pair
	 *  belongs to closest section declaration. key=value pairs with no section declarations
	 *  belong to section 'root'.
	 *  
	 *  Ini object allows you to retrieve sections and you can search those for key=value pairs.
	 */
	class Ini {
	protected:
		std::map<std::string, IniSection> config; ///< Data of ini file

		static bool isSectionHeader(const std::string &line);
		static bool isKeyValuePair(const std::string &line);
		static void getSectionIdentifier(const std::string &line, std::string &dst);
		static void getKeyValue(const std::string &line, std::string &dstKey, std::string &dstValue);

	public:
		/**
		 *  \brief Access section of ini file
		 */
		const IniSection &operator[](const std::string &section) const {
			return config.at(section);
		}

		IniSection &operator[](const std::string &section) {
			return config[section];
		}

		/**
		 *  \brief Has header section
		 *
		 *  \param [in] section Section Name
		 *
		 *  \return TRUE if yes
		 */
		bool hasSection(const std::string &section) const {
			return (config.find(section) != config.end());
		}

		/**
		 *  \brief Load config from file
		 *
		 *  \param [in] filename Path to config file
		 *
		 *  \return TRUE on success
		 *
		 *  \details key=value pairs that don't belong to any section are contained
		 *  withing section named 'root'
		 */
		void loadFromFile(const std::string &filename);
		
		/**
		 *  \brief Save config to file
		 *
		 *  \param [in] filename Path to config file
		 *
		 *  \return TRUE on success
		 */
		void saveToFile(const std::string &filename);
	};
}
