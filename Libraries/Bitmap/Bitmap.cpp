#include <fstream>
#include <iostream>
#include <cmath>

#include "Bitmap.hpp"
#include "RawHeaders.hpp"

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

		save.write((char*)(&bmpHeader), sizeof(raw::BmpHeader));
		save.write((char*)(&dibHeader), sizeof(raw::DibHeader));

		for (auto &color : palette.colors) {
			raw::Color rawColor(color);
			save.write((char*)(&rawColor), sizeof(raw::Color));
		}

		for (uint32_t cnt = 0, y = height - 1; cnt < height; cnt++, y--) {
			for (uint32_t x = 0; x < width; x++) {
				save.write((char*)(&data[y * width + x]), 1);
			}
			
			if (width % 4 != 0) {
				for (int i = width % sizeof(uint32_t); i < 4; i++) {
					save << uint8_t(0);
				}
			}
		}

		save.close();
		save.clear();
	}
	catch (std::exception &e) {
        std::cerr << "Bitmap::Exception: " << e.what() << std::endl;
	}
}

void loadFromFile(const std::string &filename) {
	raw::BmpHeader bmpHeader;
	raw::DibHeader dibHeader;

	bmp::Bitmap result;

	try {
		std::ifstream load(filename, std::ios::binary);

		load.read((char*)(&bmpHeader), sizeof(raw::BmpHeader));
		load.read((char*)(&dibHeader), sizeof(raw::DibHeader));

		if (not bmpheader.isValid()) throw std::runtime_error("Invalid BMP header");
		if (not dibHeader.isValid8bit()) throw std::runtime_error("DIB header is not valid for 8bit bitmap");

		result.create(dibHeader.width, dibHeader.height);
		result.setPalette(loadPaletteFromStream(load));
		result.data = loadPixelsFromStream(load);

		load.close();
		load.clear();
	}
	catch (std::exception &e) {
        std::cerr << "Bitmap::Exception: " << e.what() << std::endl;
	}

	*this = result;
}

bmp::Palette loadPaletteFromStream(std::ifstream &load) {
	bmp::Palette pal;
	raw::Color color;
	for (unsigned i = 0; i < 256; i++) {
		load.read((char*)(&color), sizeof(raw::Color));
		pal.colors[i] = color.toBmpColor();
	}

	return pal;
}

bmp::Bitmap::Bitmap() {
    width = 0;
    height = 0;
    palette = bmp::Palette::getGrayscalePalette();
}