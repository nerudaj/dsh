#include <catch.hpp>
#include <RawHeaders.hpp>
#include <fstream>
#include <IO.hpp>

#include "Comparators.hpp"

TEST_CASE("BmpHeader isValid()", "[BmpHeader]") {
	raw::BmpHeader header(1000);
	REQUIRE(header.isValid());
}

TEST_CASE("DibHeader isValid8bit()", "[DibHeader]") {
	raw::DibHeader header(10, 100);
	REQUIRE(header.isValid8bit());
}

struct PixelData {
	std::vector<uint8_t> pixels;
	uint32_t width, height;

	PixelData(const std::vector<uint8_t> &pixels, uint32_t width, uint32_t height) : pixels(pixels), width(width), height(height) {}
};

PixelData generatePixelData(int i) {
	if (i == 0) return PixelData({}, 0, 0);
	else if (i == 1) return PixelData({0, 1, 2, 3}, 2, 2);
	return PixelData({0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15}, 4, 4);
}

TEST_CASE("IO save load operations", "[IO]") {
	SECTION("BmphHader") {
		unsigned pixelCount = GENERATE(0, 1000);

		std::ofstream save("test.bmp", std::ios::binary);
		raw::BmpHeader bmp(pixelCount);
		IO::saveBmpHeaderToStream(bmp, save);
		save.close();
		save.clear();

		std::ifstream load("test.bmp", std::ios::binary);
		raw::BmpHeader ref;
		IO::loadBmpHeaderFromStream(ref, load);
		load.close();
		load.clear();

		REQUIRE(bmp == ref);
	}

	SECTION("DibHeader") {
		unsigned width = GENERATE(0, 4, 10, 15);
		unsigned height = GENERATE(0, 4, 10, 15);

		std::ofstream save("test.bmp", std::ios::binary);
		raw::DibHeader dib(width, height);
		IO::saveDibHeaderToStream(dib, save);
		save.close();
		save.clear();

		std::ifstream load("test.bmp", std::ios::binary);
		raw::DibHeader ref;
		IO::loadDibHeaderFromStream(ref, load);
		load.close();
		load.clear();

		REQUIRE(dib == ref);
	}

	SECTION("Palette") {
		std::ofstream save("test.bmp", std::ios::binary);
		bmp::Palette pal = bmp::Palette::getGrayscalePalette();
		IO::savePaletteToStream(pal, save);
		save.close();
		save.clear();

		std::ifstream load("test.bmp", std::ios::binary);
		bmp::Palette ref = IO::loadPaletteFromStream(load);
		load.close();
		load.clear();

		REQUIRE(pal == ref);
	}

	SECTION("Pixels") {
		int i = GENERATE(0, 1, 2);
		PixelData data = generatePixelData(i);

		std::ofstream save("test.bmp", std::ios::binary);
		IO::savePixelsToStream(data.pixels, data.width, save);
		save.close();
		save.clear();

		std::ifstream load("test.bmp", std::ios::binary);
		std::vector<uint8_t> ref = IO::loadPixelsFromStream(load, data.width, data.height);
		load.close();
		load.clear();

		REQUIRE(data.pixels == ref);
	}
}
#include <iostream>
TEST_CASE("BitmapSaveLoadTest", "[Bitmap]") {
	bmp::Bitmap bmp;
	bmp.create(15, 15);
	bmp.setPalette(bmp::Palette::getUnixPalette());

	for (unsigned y = 0; y < 15; y++) {
		for (unsigned x = 0; x < 15; x++) {
			bmp.setPixel(x, y, (y * 15 + x) % 256);
		}
	}
	bmp.saveToFile("test.bmp");

	bmp::Bitmap ref;
	ref.loadFromFile("test.bmp");

	SECTION("Does palette match") {
		REQUIRE(bmp.getPalette() == ref.getPalette());
	}
	
	SECTION("Does width match") {
		REQUIRE(bmp.getWidth() == ref.getWidth());
	}
	
	SECTION("Does height match") {
		REQUIRE(bmp.getHeight() == ref.getHeight());
	}
	
	SECTION("Do pixels match") {
		const auto width = bmp.getWidth();
		const auto height= bmp.getHeight();

		auto x = GENERATE_COPY(range(0u, width));
		auto y = GENERATE_COPY(range(0u, height));

		REQUIRE(bmp.getPixel(x, y) == ref.getPixel(x, y));
	}
}
