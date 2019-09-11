#include "RawHeaders.hpp"

const uint32_t COLOR_COUNT_IN_PALETTE = 256;

raw::BmpHeader::BmpHeader(size_t pixelCount) {
    identity = 0x4d42; // "MB", will export as BM
	sizeOfFile = sizeof(raw::BmpHeader) + sizeof(raw::DibHeader) + COLOR_COUNT_IN_PALETTE * sizeof(uint32_t) + pixelCount;
	reserved1 = 0;
	reserved2 = 0;
	dataOffset = sizeof(raw::BmpHeader) + sizeof(raw::DibHeader) + COLOR_COUNT_IN_PALETTE * sizeof(uint32_t);
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