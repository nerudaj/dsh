#pragma once

#include <cstdint>
#include <vector>

namespace bmp {
	struct Color {
		uint8_t red;
		uint8_t green;
		uint8_t blue;
	};

	struct Palette {
		Color colors[256];
	};

	class Bitmap {
	private:
		unsigned width;
		unsigned height;
		std::vector<uint8_t> data;
		Palette palette;
	};
};