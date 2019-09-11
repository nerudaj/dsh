#pragma once

#include <cstdint>
#include <vector>

namespace bmp {
	struct Color {
		uint8_t red;
		uint8_t green;
		uint8_t blue;

		Color() : red(0), green(0), blue(0) {}

		/**
		 *  \brief Grayscale constructor for Color
		 */
		Color(uint8_t c) : red(c), green(c), blue(c) {}

		/**
		 *  \brief Standard 3 color constructor for Color
		 */
		Color(uint8_t r, uint8_t g, uint8_t b) : red(r), green(g), blue(b) {}
	};

	/**
	 *  \brief For standard 256 colors bitmap, Palette defines which colors are available
	 */
	struct Palette {
		Color colors[256];

		/**
		 *  \brief Generates a grayscale palette
		 */
		static Palette getGrayscalePalette();

		/**
		 *  \brief Generates standard UNIX 8bit palette
		 */
		static Palette getUnixPalette();
	};

	class Bitmap {
	private:
		unsigned width;
		unsigned height;
		std::vector<uint8_t> data;
		Palette palette;
	
	public:
		/**
		 *  \brief Create empty bitmap canvas
		 * 
		 *  \param[in]  width   Width of the canvas
		 *  \param[in]  height  Height of the canvas
		 * 
		 *  Canvas will be filled with first references to first
		 *  color in the palette. Changing the palette with \ref
		 *  setPalette will thus change the color of the canvas
		 */
		void create(unsigned width, unsigned height);

		/**
		 *  \brief Initializes the object
		 * 
		 *  Canvas is empty width zero width and height.
		 *  Palette is set to grayscale
		 */
		Bitmap();
	};
};