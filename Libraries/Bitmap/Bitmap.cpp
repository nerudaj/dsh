#include "Bitmap.hpp"
#include <fstream>
#include <iostream>

using bmp::Color;
using bmp::Image;

void Image::computeHeaders() {
	bmpHeader.identity = 0x4d42; // "MB", will export as BM
	bmpHeader.sizeOfFile = sizeof(bmpHeader) + sizeof(dibHeader) + colors.size() * sizeof(uint32_t) + pixels.size();
	bmpHeader.reserved1 = 0;
	bmpHeader.reserved2 = 0;
	bmpHeader.dataOffset = sizeof(bmpHeader) + sizeof(dibHeader) + colors.size() * sizeof(uint32_t);
	
	dibHeader.sizeOfDibHeader = sizeof(dibHeader);
	// width and height already set
	dibHeader.plane = 1;
	dibHeader.bitsPerPixel = 8;
	dibHeader.compression = 0;
	dibHeader.sizeRaw = pixels.size();
	dibHeader.printWidth = 0;
	dibHeader.printHeight = 0;
	dibHeader.nofColorsInPalette = 256;
	dibHeader.importantColors = 0;
}

void Image::generateBasicPalette() {
	
}

void Image::generateGrayscalePalette() {
	colors.resize(256);
	for (int i = 0; i < 256; i++) {
		colors[i] = { uint8_t(i), uint8_t(i), uint8_t(i), 0};
	}
}

bool Image::loadFromFile(const std::string &filename) {
	try {
		std::ifstream load(filename);
		
		// TODO: This
		
		load.close();
		load.clear();
	}
	catch (std::exception &e) {
		log.error("Image", "Exception: " + std::string(e.what()));
		return false;
	}
	
	return true;
}

bool Image::saveToFile(const std::string &filename) {
	computeHeaders();
	
	try {
		std::ofstream save(filename, std::ios::binary);
		
		save.write((char*)(&bmpHeader), sizeof(bmpHeader));
		save.write((char*)(&dibHeader), sizeof(dibHeader));
		
		for (auto color : colors) {
			save.write((char*)(&color), sizeof(Color));
		}
		
		for (uint32_t cnt = 0, y = dibHeader.height - 1; cnt < dibHeader.height; cnt++, y--) {
			for (uint32_t x = 0; x < dibHeader.width; x++) {
				save.write((char*)(&pixels[x * dibHeader.width + y]), 1);
			}
			
			if (dibHeader.width % 4 != 0) {
				for (int i = dibHeader.width % sizeof(uint32_t); i <= 4; i++) {
					save << uint8_t(0);
				}
			}
		}
		
		save.close();
		save.clear();
	}
	catch (std::exception &e) {
		log.error("Image", "Exception: " + std::string(e.what()));
		return false;
	}
	
	return true;
}

bool Image::create(uint32_t width, uint32_t height) {
	try {
		pixels.resize(width * height);
		for (auto &pixel : pixels) pixel = 255;
	}
	catch (std::exception &e) {
		log.error("Image", "Exception: " + std::string(e.what()));
		return false;
	}
	
	dibHeader.width = width;
	dibHeader.height = height;
	
	return true;
}

void Image::setPixel(uint32_t x, uint32_t y, uint8_t value) {
	pixels[y * dibHeader.width + x] = value;
}

void Image::setPalette(const std::vector<Color> &palette) {
	colors = palette;
	
	while (colors.size() > 256) colors.pop_back();
	while (colors.size() < 256) colors.push_back({255, 255, 255, 0});
}

void Image::setPalette(PaletteID id) {
	switch (id) {
	case PaletteID::Basic:
		generateBasicPalette();
		break;
	
	case PaletteID::Grayscale:
		generateGrayscalePalette();
		break;
	}
}