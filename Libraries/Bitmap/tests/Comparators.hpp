#pragma once

#include <RawHeaders.hpp>

bool operator==(const bmp::Color &a, const bmp::Color &b) {
	return  a.red == b.red &&
			a.green == b.green &&
			a.blue == b.blue;
}

bool operator!=(const bmp::Color &a, const bmp::Color &b) {
	return !(a == b);
}

bool arePalettesSame(const bmp::Palette &a, const bmp::Palette &b) {
	for (unsigned i = 0; i < 256; i++) {
		if (a.colors[i] != b.colors[i]) return false;
	}
	
	return true;
}

bool operator==(const std::vector<uint8_t> &a, const std::vector<uint8_t> &b) {
	if (a.size() != b.size()) return false;
	
	for (unsigned i = 0; i < a.size(); i++) {
		if (a[i] != b[i]) return false;
	}
	
	return true;
}