#include <fstream>
#include <iostream>
#include <cmath>
#include <ciso646>

#include "Bitmap.hpp"
#include "RawHeaders.hpp"
#include "IO.hpp"

void bmp::Bitmap::create(unsigned width, unsigned height) {
	data.resize(width * height, 0);
	bmp::Bitmap::width = width;
	bmp::Bitmap::height = height;
}

void bmp::Bitmap::resize(unsigned w, unsigned h) {
	bmp::Bitmap result;
	result.create(w, h);
	result.setPalette(getPalette());

	float kW = float(w) / width;
	float kH = float(h) / height;
	
	for (unsigned y = 0; y < h; y++) {
		for (unsigned x = 0; x < w; x++) {
			uint8_t value = getPixel(x / kW, y / kH);
			result.setPixel(x, y, value);
		}
	}

	*this = result;
}


void bmp::Bitmap::saveToFile(const std::string &filename) const {
	raw::BmpHeader bmpHeader(width * height);
	raw::DibHeader dibHeader(width, height);
	
	try {
		std::ofstream save(filename, std::ios::binary);

		IO::saveBmpHeaderToStream(bmpHeader, save);
		IO::saveDibHeaderToStream(dibHeader, save);
		IO::savePaletteToStream(palette, save);
		IO::savePixelsToStream(data, width, save);

		save.close();
		save.clear();
	}
	catch (std::exception &e) {
		std::cerr << "Bitmap::Exception: " << e.what() << std::endl;
	}
}

void bmp::Bitmap::loadFromFile(const std::string &filename) {
	raw::BmpHeader bmpHeader;
	raw::DibHeader dibHeader;
	bmp::Bitmap result;

	try {
		std::ifstream load(filename, std::ios::binary);

		IO::loadBmpHeaderFromStream(bmpHeader, load);
		IO::loadDibHeaderFromStream(dibHeader, load);

		if (not bmpHeader.isValid()) throw std::runtime_error("Invalid BMP header");
		if (not dibHeader.isValid8bit()) throw std::runtime_error("DIB header is not valid for 8bit bitmap");

		result.create(dibHeader.width, dibHeader.height);
		result.setPalette(IO::loadPaletteFromStream(load));
		result.data = IO::loadPixelsFromStream(load, dibHeader.width, dibHeader.height);

		load.close();
		load.clear();
	}
	catch (std::exception &e) {
		std::cerr << "Bitmap::Exception: " << e.what() << std::endl;
	}

	*this = result;
}

bmp::Bitmap::Bitmap() {
	width = 0;
	height = 0;
	palette = bmp::Palette::getGrayscalePalette();
}