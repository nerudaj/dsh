#pragma once

#include <cstdint>
#include <vector>
#include <fstream>

#include "Bitmap.hpp"
#include "RawHeaders.hpp"

class IO {
public:
	static void saveBmpHeaderToStream(const raw::BmpHeader &bmp, std::ofstream &save) {
		save.write((char*)(&bmp), sizeof(raw::BmpHeader));
	}
	
	static void saveDibHeaderToStream(const raw::DibHeader &dib, std::ofstream &save) {
		save.write((char*)(&dib), sizeof(raw::DibHeader));
	}
	
	static void savePaletteToStream(const bmp::Palette &palette, std::ofstream &save);
	
	static void savePixelsToStream(const std::vector<uint8_t> &pixels, uint32_t rowWidth, std::ofstream &save);

	static void loadBmpHeaderFromStream(raw::BmpHeader &bmp, std::ifstream &load) {
		load.read((char*)(&bmp), sizeof(raw::BmpHeader));
	}
	
	static void loadDibHeaderFromStream(raw::DibHeader &dib, std::ifstream &load) {
		load.read((char*)(&dib), sizeof(raw::DibHeader));
	}
	
	static bmp::Palette loadPaletteFromStream(std::ifstream &load);
	static std::vector<uint8_t> loadPixelsFromStream(std::ifstream &load, uint32_t width, uint32_t height);
};