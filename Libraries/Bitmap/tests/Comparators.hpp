#pragma once

#include <RawHeaders.hpp>

bool operator==(const raw::BmpHeader &a, const raw::BmpHeader &b) {
	return  a.identity == b.identity &&
			a.sizeOfFile == b.sizeOfFile &&
			a.reserved1 == b.reserved1 &&
			a.reserved2 == b.reserved2 &&
			a.dataOffset == b.dataOffset;
}

bool operator==(const raw::DibHeader &a, const raw::DibHeader &b) {
	return  a.sizeOfDibHeader == b.sizeOfDibHeader &&
			a.width == b.width &&
			a.height == b.height && 
			a.plane == b.plane &&
			a.bitsPerPixel == b.bitsPerPixel &&
			a.compression == b.compression &&
			a.sizeRaw == b.sizeRaw &&
			a.printWidth == b.printWidth && 
			a.printHeight ==  b.printHeight &&
			a.nofColorsInPalette == b.nofColorsInPalette &&
			a.importantColors == b.importantColors;
}

bool operator==(const bmp::Color &a, const bmp::Color &b) {
	return  a.red == b.red &&
			a.green == b.green &&
			a.blue == b.blue;
}

bool operator!=(const bmp::Color &a, const bmp::Color &b) {
	return !(a == b);
}

bool operator==(const bmp::Palette &a, const bmp::Palette &b) {
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