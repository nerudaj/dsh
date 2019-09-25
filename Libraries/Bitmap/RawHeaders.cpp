#include "RawHeaders.hpp"

const uint32_t COLOR_COUNT_IN_PALETTE = 256;

const uint16_t BM_IDENTIFIER = 0x4d42;

raw::BmpHeader::BmpHeader(size_t pixelCount) {
    identity = BM_IDENTIFIER; // "MB", will export as BM
	sizeOfFile = sizeof(raw::BmpHeader) + sizeof(raw::DibHeader) + COLOR_COUNT_IN_PALETTE * sizeof(uint32_t) + pixelCount;
	reserved1 = 0;
	reserved2 = 0;
	dataOffset = sizeof(raw::BmpHeader) + sizeof(raw::DibHeader) + COLOR_COUNT_IN_PALETTE * sizeof(uint32_t);
}

bool raw::BmpHeader::isValid() const {
	bool valid = true;
	valid &= identity == BM_IDENTIFIER;
	valid &= reserved1 == 0;
	valid &= reserved2 == 0;
	valid &= sizeOfFile > (sizeof(raw::BmpHeader) + sizeof(raw::DibHeader) + COLOR_COUNT_IN_PALETTE * sizeof(uint32_t));
	valid &= dataOffset == (sizeof(raw::BmpHeader) + sizeof(raw::DibHeader) + COLOR_COUNT_IN_PALETTE * sizeof(uint32_t));
	return valid;
}

raw::DibHeader::DibHeader(uint32_t w, uint32_t h) {
    sizeOfDibHeader = sizeof(raw::DibHeader);
	width = w;
    height = h;
	plane = 1;
	bitsPerPixel = 8;
	compression = 0;
	sizeRaw = w * h;
	printWidth = 0;
	printHeight = 0;
	nofColorsInPalette = COLOR_COUNT_IN_PALETTE;
	importantColors = 0;
}

bool raw::DibHeader::isValid8bit() const {
	bool valid = true;
	valid &= sizeOfDibHeader == sizeof(raw::DibHeader);
	valid &= plane == 1;
	valid &= bitsPerPixel == 8;
	valid &= compression == 0;
	valid &= nofColorsInPalette == COLOR_COUNT_IN_PALETTE;
	valid &= importantColors == 0;
	return valid;
}