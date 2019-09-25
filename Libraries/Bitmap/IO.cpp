#include "IO.hpp"

void IO::savePaletteToStream(const bmp::Palette &palette, std::ofstream &save) {
	for (auto &color : palette.colors) {
		raw::Color rawColor(color);
		save.write((char*)(&rawColor), sizeof(raw::Color));
	}
}

void IO::savePixelsToStream(const std::vector<uint8_t> &pixels, uint32_t width, std::ofstream &save) {
	if (width == 0) return;
	
	uint32_t height = pixels.size() / width;
	for (uint32_t cnt = 0, y = height - 1; cnt < height; cnt++, y--) {
		for (uint32_t x = 0; x < width; x++) {
			save.write((char*)(&pixels[y * width + x]), 1);
		}
		
		if (width % 4 != 0) {
			for (int i = width % sizeof(uint32_t); i < 4; i++) {
				save << uint8_t(0);
			}
		}
	}
}

bmp::Palette IO::loadPaletteFromStream(std::ifstream &load) {
	bmp::Palette pal;
	raw::Color color;
	for (unsigned i = 0; i < 256; i++) {
		load.read((char*)(&color), sizeof(raw::Color));
		pal.colors[i] = color.toBmpColor();
	}

	return pal;
}

std::vector<uint8_t> IO::loadPixelsFromStream(std::ifstream &load, uint32_t width, uint32_t height) {
	std::vector<uint8_t> result(width * height, 0);

	for (uint32_t y = 0; y < height; y++) {
		for (uint32_t x = 0; x < width; x++) {
			load.read((char*)(&result[(height - 1 - y) * width + x]), sizeof(uint8_t));
		}
		
		if (width % 4 != 0) {
			char dummy;
			for (int i = width % sizeof(uint32_t); i < 4; i++) {
				load.read(&dummy, sizeof(uint8_t));
			}
		}
	}

	return result;
}