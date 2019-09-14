#include <fstream>
#include <iostream>

#include "Bitmap.hpp"
#include "RawHeaders.hpp"

void bmp::Bitmap::create(unsigned width, unsigned height) {
    data.resize(width * height, 0);
    bmp::Bitmap::width = width;
    bmp::Bitmap::height = height;
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

bmp::Bitmap::Bitmap() {
    width = 0;
    height = 0;
    palette = bmp::Palette::getGrayscalePalette();
}