#include "ConfigItem.hpp"
#include <ciso646>
#include <cstdlib>

long ConfigItem::asInt() const {
	return strtol(value.c_str(), NULL, 10);
}

float ConfigItem::asFloat() const {
	return strtof(value.c_str(), NULL);
}

const std::string &ConfigItem::asString() const {
	return value;
}

bool ConfigItem::asBool() const {
	return !(value == "0" or value == "false" or value == "False" or value == "FALSE");
}

ConfigItem &ConfigItem::operator=(const char *value) {
	ConfigItem::value = value;
	return (*this);
}
	
ConfigItem &ConfigItem::operator=(const std::string &value) {
	ConfigItem::value = value;
	return (*this);
}

ConfigItem &ConfigItem::operator=(const bool value) {
	if (value) {
		ConfigItem::value = "1";
	}
	else {
		ConfigItem::value = "0";
	}
	return (*this);
}

ConfigItem &ConfigItem::operator=(const int value) {
	ConfigItem::value = std::to_string(value);
	return *this;
}

ConfigItem &ConfigItem::operator=(const long value) {
	ConfigItem::value = std::to_string(value);
	return *this;
}

ConfigItem &ConfigItem::operator=(const float value) {
	ConfigItem::value = std::to_string(value);
	return *this;
}

bool ConfigItem::operator==(const char *value) const {
	return ConfigItem::value == std::string(value);
}

bool ConfigItem::operator==(const std::string &value) const {
	return ConfigItem::value == value;
}

bool ConfigItem::operator==(const bool value) const {
	return asBool() == value;
}

bool ConfigItem::operator==(const int value) const {
	return asInt() == value;
}

bool ConfigItem::operator==(const long value) const {
	return asInt() == value;
}

bool ConfigItem::operator==(const float value) const {
	return asFloat() == value;
}

ConfigItem::ConfigItem() {
	
}

ConfigItem::~ConfigItem() {
	
}
