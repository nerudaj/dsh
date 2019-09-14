#pragma once

#include <cstdint>
#include <vector>
#include <string>

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
		 *  \brief Resize image
		 * 
		 *  \param[in]  width   New width of image
		 *  \param[in]  height  New height of image
		 * 
		 *  \note You might lost some data during resize.
		 * 
		 *  No color interpolation is performed.
		 */
		void resize(unsigned width, unsigned height);

		/**
		 *  \brief Set the value of pixel
		 * 
		 *  \param[in]  x      X coordinate of pixel
		 *  \param[in]  y      Y coordinate of pixel
		 *  \param[in]  value  Index to color palette
		 */
		void setPixel(unsigned x, unsigned y, uint8_t value) {
			data[y * width + x] = value;
		}

		/**
		 *  \brief Get value of a pixel (index to color palette)
		 * 
		 *  \param[in]  x      X coordinate of pixel
		 *  \param[in]  y      Y coordinate of pixel
		 */
		uint8_t getPixel(unsigned x, unsigned y) const {
			return data[y * width + x];
		}

		/**
		 *  \brief Change currently used palette
		 * 
		 *  \param[in]  palette  New palette to use
		 * 
		 *  Chaning the palette won't affect the image data,
		 *  only pixel colors. If can simply convert image
		 *  from colored to grayscale by only changing the palette
		 *  and then you can roll back by setting it back.
		 */
		void setPalette(const bmp::Palette &palette) {
			this->palette = palette;
		}

		/**
		 *  \brief Get currently used palette
		 */
		const bmp::Palette &getPalette() const {
			return palette;
		}

		/**
		 *  \brief Store bitmap to file
		 * 
		 *  \param[in]  filename  Name of the output file
		 */
		void saveToFile(const std::string &filename) const;

		/**
		 *  \brief Initializes the object
		 * 
		 *  Canvas is empty width zero width and height.
		 *  Palette is set to grayscale
		 */
		Bitmap();
	};
};