#ifndef ITEM_HPP_
#define ITEM_HPP_

#include <string>
#include <iostream>

namespace cfg {
	class Item {
	protected:
		std::string value;

	public:
		long asInt() const { return strtol(value.c_str(), NULL, 10); }
		float asFloat() const { return strtof(value.c_str(), NULL); }
		const std::string &asString() const { return value; }
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
		~Item();
	};
}

#endif
