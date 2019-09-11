#pragma once

#include <cstdint>
#include <vector>

namespace bmp {
	struct Color {
		uint8_t red;
		uint8_t green;
		uint8_t blue;

		Color(uint8_t c) : red(c), green(c), blue(c) {}
		Color(uint8_t r, uint8_t g, uint8_t b) : red(r), green(g), blue(b) {}
	};

	struct Palette {
		Color colors[256];

		static Palette getGrayscalePalette();

		static Palette getUnixPalette();
	};

	class Bitmap {
	private:
		unsigned width;
		unsigned height;
		std::vector<uint8_t> data;
		Palette palette;
	
	public:
		void create(unsigned width, unsigned height);

		Bitmap();
	};
};