#ifndef ITEM_HPP_
#define ITEM_HPP_

#include <string>
#include <iostream>

namespace cfg {
	/**
	 *  \brief General type storage class
	 *  
	 *  \details This class can be used to store string/integer/bool/float values and read
	 *  them in different formats. Read type is independent on original write format.
	 */
	class Item {
	protected:
		std::string value; ///< Internal storage for the value

	public:
		/**
		 *  \brief Get integer interpretation of value
		 */
		long asInt() const { return strtol(value.c_str(), NULL, 10); }
		
		/**
		 *  \brief Get float interpretation of value
		 */
		float asFloat() const { return strtof(value.c_str(), NULL); }
		
		/**
		 *  \brief Get string interpretation of value
		 */
		const std::string &asString() const { return value; }
		
		/**
		 *  \brief Get boolean interpretation of value
		 */
		bool asBool() const { return !(value == "0" or value == "false" or value == "False" or value == "FALSE"); }

		Item &operator=(const char *value);
		Item &operator=(const std::string &value);
		Item &operator=(const bool value);
		Item &operator=(const int value);
		Item &operator=(const long value);
		Item &operator=(const float value);

		bool operator==(const char *value) const { return Item::value == std::string(value); }
		bool operator==(const std::string &value) const { return Item::value == value; }
		bool operator==(const bool value) const { return asBool() == value; }
		bool operator==(const int value) const { return asInt() == value; }
		bool operator==(const long value) const { return asInt() == value; }
		bool operator==(const float value) const { return asFloat() == value; }

		Item();
		Item(const char *value);
		Item(const std::string &value);
		Item(const bool value);
		Item(const int value);
		Item(const long value);
		Item(const float value);
		~Item();
	};
}

#endif
