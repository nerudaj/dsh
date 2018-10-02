#include "Item.hpp"
#include <ciso646>
#include <cstdlib>

using namespace cfg;

Item &Item::operator=(const char *value) {
	Item::value = value;
	return (*this);
}
	
Item &Item::operator=(const std::string &value) {
	Item::value = value;
	return (*this);
}

Item &Item::operator=(const bool value) {
	if (value) {
		Item::value = "1";
	}
	else {
		Item::value = "0";
	}
	return (*this);
}

Item &Item::operator=(const int value) {
	Item::value = std::to_string(value);
	return *this;
}

Item &Item::operator=(const long value) {
	Item::value = std::to_string(value);
	return *this;
}

Item &Item::operator=(const float value) {
	Item::value = std::to_string(value);
	return *this;
}

Item::Item() {
	
}

Item::Item(const char *value) {
	*this = value;
}

Item::Item(const std::string &value) {
	*this = value;
}

Item::Item(const bool value) {
	*this = value;
}

Item::Item(const int value) {
	*this = value;
}

Item::Item(const long value) {
	*this = value;
}

Item::Item(const float value) {
	*this = value;
}

Item::~Item() {
	
}
