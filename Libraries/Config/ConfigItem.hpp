#ifndef CONFIG_ITEM_HPP_
#define CONFIG_ITEM_HPP_

#include <string>
#include <iostream>

class ConfigItem {
protected:
	std::string value;

public:
	long asInt() const;
	float asFloat() const;
	const std::string &asString() const;
	bool asBool() const;

	ConfigItem &operator=(const char *value);
	ConfigItem &operator=(const std::string &value);
	ConfigItem &operator=(const bool value);
	ConfigItem &operator=(const int value);
	ConfigItem &operator=(const long value);
	ConfigItem &operator=(const float value);
	
	bool operator==(const char *value) const;
	bool operator==(const std::string &value) const;
	bool operator==(const bool value) const;
	bool operator==(const int value) const;
	bool operator==(const long value) const;
	bool operator==(const float value) const;

	ConfigItem();
	~ConfigItem();
};

#endif
