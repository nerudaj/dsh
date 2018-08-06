#ifndef INI_HPP_
#define INI_HPP_

#include "Item.hpp"
#include <map>

namespace cfg {
	class IniSection : public std::map<std::string, Item> {
	public:
		bool hasKey(const std::string &key) { return find(key) != end(); }
	};

	class Ini {
	protected:
		std::map<std::string, IniSection> config;

		static bool isSectionHeader(const std::string &line);
		static bool isKeyValuePair(const std::string &line);
		static void getSectionIdentifier(const std::string &line, std::string &dst);
		static void getKeyValue(const std::string &line, std::string &dstKey, std::string &dstValue);

	public:
		const IniSection &operator[](const std::string &section) const {
			return config.at(section);
		}

		IniSection &operator[](const std::string &section) {
			auto &tmp = config[section];
			return tmp;
		}

		/**
		 *  \brief Has header section
		 *
		 *  \param [in] section Section Name
		 *
		 *  \return TRUE if yes
		 */
		bool hasSection(const std::string &section) const { return (config.find(section) != config.end()); }

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
		bool loadFromFile(const std::string &filename);
		
		/**
		 *  \brief Save config to file
		 *
		 *  \param [in] filename Path to config file
		 *
		 *  \return TRUE on success
		 */
		bool saveToFile(const std::string &filename);
	};
}

#endif
