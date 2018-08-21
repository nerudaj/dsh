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
	// From https://stackoverflow.com/questions/17583020/how-to-generate-256-color-palette-for-linux-terminal-in-html-jquery
	std::vector<uint32_t> palette = {
		0x00000000, 0x00808080, 0x00800000, 0x00ff0000, 0x00008000, 0x0000ff00, 0x00808000, 0x00ffff00, 0x00000080, 0x000000ff, 0x00800080, 0x00ff00ff, 0x00008080, 0x0000ffff, 0x00c0c0c0, 0x00ffffff, 0x00000000, 0x00af0000, 0x0000005f, 0x00af005f, 0x00000087, 0x00af0087, 0x000000af, 0x00af00af, 0x000000d7, 0x00af00d7, 0x000000ff, 0x00af00ff, 0x00005f00, 0x00af5f00, 0x00005f5f, 0x00af5f5f, 0x00005f87, 0x00af5f87, 0x00005faf, 0x00af5faf, 0x00005fd7, 0x00af5fd7, 0x00005fff, 0x00af5fff, 0x00008700, 0x00af8700, 0x0000875f, 0x00af875f, 0x00008787, 0x00af8787, 0x000087af, 0x00af87af, 0x000087d7, 0x00af87d7, 0x000087ff, 0x00af87ff, 0x0000af00, 0x00afaf00, 0x0000af5f, 0x00afaf5f, 0x0000af87, 0x00afaf87, 0x0000afaf, 0x00afafaf, 0x0000afd7, 0x00afafd7, 0x0000afff, 0x00afafff, 0x0000d700, 0x00afd700, 0x0000d75f, 0x00afd75f, 0x0000d787, 0x00afd787, 0x0000d7af, 0x00afd7af, 0x0000d7d7, 0x00afd7d7, 0x0000d7ff, 0x00afd7ff, 0x0000ff00, 0x00afff00, 0x0000ff5f, 0x00afff5f, 0x0000ff87, 0x00afff87, 0x0000ffaf, 0x00afffaf, 0x0000ffd7, 0x00afffd7, 0x0000ffff, 0x00afffff, 0x005f0000, 0x00d70000, 0x005f005f, 0x00d7005f, 0x005f0087, 0x00d70087, 0x005f00af, 0x00d700af, 0x005f00d7, 0x00d700d7, 0x005f00ff, 0x00d700ff, 0x005f5f00, 0x00d75f00, 0x005f5f5f, 0x00d75f5f, 0x005f5f87, 0x00d75f87, 0x005f5faf, 0x00d75faf, 0x005f5fd7, 0x00d75fd7, 0x005f5fff, 0x00d75fff, 0x005f8700, 0x00d78700, 0x005f875f, 0x00d7875f, 0x005f8787, 0x00d78787, 0x005f87af, 0x00d787af, 0x005f87d7, 0x00d787d7, 0x005f87ff, 0x00d787ff, 0x005faf00, 0x00d7af00, 0x005faf5f, 0x00d7af5f, 0x005faf87, 0x00d7af87, 0x005fafaf, 0x00d7afaf, 0x005fafd7, 0x00d7afd7, 0x005fafff, 0x00d7afff, 0x005fd700, 0x00d7d700, 0x005fd75f, 0x00d7d75f, 0x005fd787, 0x00d7d787, 0x005fd7af, 0x00d7d7af, 0x005fd7d7, 0x00d7d7d7, 0x005fd7ff, 0x00d7d7ff, 0x005fff00, 0x00d7ff00, 0x005fff5f, 0x00d7ff5f, 0x005fff87, 0x00d7ff87, 0x005fffaf, 0x00d7ffaf, 0x005fffd7, 0x00d7ffd7, 0x005fffff, 0x00d7ffff, 0x00870000, 0x00ff0000, 0x0087005f, 0x00ff005f, 0x00870087, 0x00ff0087, 0x008700af, 0x00ff00af, 0x008700d7, 0x00ff00d7, 0x008700ff, 0x00ff00ff, 0x00875f00, 0x00ff5f00, 0x00875f5f, 0x00ff5f5f, 0x00875f87, 0x00ff5f87, 0x00875faf, 0x00ff5faf, 0x00875fd7, 0x00ff5fd7, 0x00875fff, 0x00ff5fff, 0x00878700, 0x00ff8700, 0x0087875f, 0x00ff875f, 0x00878787, 0x00ff8787, 0x008787af, 0x00ff87af, 0x008787d7, 0x00ff87d7, 0x008787ff, 0x00ff87ff, 0x0087af00, 0x00ffaf00, 0x0087af5f, 0x00ffaf5f, 0x0087af87, 0x00ffaf87, 0x0087afaf, 0x00ffafaf, 0x0087afd7, 0x00ffafd7, 0x0087afff, 0x00ffafff, 0x0087d700, 0x00ffd700, 0x0087d75f, 0x00ffd75f, 0x0087d787, 0x00ffd787, 0x0087d7af, 0x00ffd7af, 0x0087d7d7, 0x00ffd7d7, 0x0087d7ff, 0x00ffd7ff, 0x0087ff00, 0x00ffff00, 0x0087ff5f, 0x00ffff5f, 0x0087ff87, 0x00ffff87, 0x0087ffaf, 0x00ffffaf, 0x0087ffd7, 0x00ffffd7, 0x0087ffff, 0x00ffffff, 0x00080808, 0x00808080, 0x00121212, 0x008a8a8a, 0x001c1c1c, 0x00949494, 0x00262626, 0x009e9e9e, 0x00303030, 0x00a8a8a8, 0x003a3a3a, 0x00b2b2b2, 0x00444444, 0x00bcbcbc, 0x004e4e4e, 0x00c6c6c6, 0x00585858, 0x00d0d0d0, 0x00626262, 0x00dadada, 0x006c6c6c, 0x00e4e4e4, 0x00767676, 0x00eeeeee
	};
	
	colors.resize(256);
	for (unsigned i = 0; i < palette.size(); i++) {
		uint8_t red = ((palette[i] & 0x00ff0000) >> 16);
		uint8_t green = ((palette[i] & 0x0000ff00) >> 8);
		uint8_t blue = palette[i] & 0x000000ff;
		colors[i] = { blue, green, red, 0 };
	}
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