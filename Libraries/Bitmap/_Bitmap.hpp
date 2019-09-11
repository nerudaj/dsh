#ifndef BITMAP_HPP_
#define BITMAP_HPP_

#include <cstdlib>
#include <vector>
#include <iostream>

namespace bmp {
	#pragma pack(1)
	struct Color {
		uint8_t blue;
		uint8_t green;
		uint8_t red;
		uint8_t alpha;
	};
	#pragma pack()

	class Image {
	protected:
		#pragma pack(1)
		struct {
			uint16_t identity; ///< String "BM"
			uint32_t sizeOfFile; ///< size of file (headers + data)
			uint16_t reserved1; ///< 0x0000
			uint16_t reserved2; ///< 0x0000
			uint32_t dataOffset; ///< SIZEOF(bmpheader) + sizeof(dibheader) + palette
		} bmpHeader;
		
		struct {
			uint32_t sizeOfDibHeader; // size of this headers
			uint32_t width; ///< Width of image in pixels
			uint32_t height; ///< Height of image in pixels
			uint16_t plane; ///< Number of color planes
			uint16_t bitsPerPixel; ///< 8, 16, 24, 32
			uint32_t compression; ///< 0 - none
			uint32_t sizeRaw; ///< Size of raw bitmap data with padding
			uint32_t printWidth; ///< pixels/metre horizontal
			uint32_t printHeight; ///< pixels/metre vertical
			uint32_t nofColorsInPalette;
			uint32_t importantColors; ///< 0 - All
		} dibHeader;
		#pragma pack()

		std::vector<bmp::Color> colors;
		std::vector<uint8_t> pixels;
		
		void computeHeaders();
		void generateBasicPalette();
		void generateGrayscalePalette();
		
	public:
		enum PaletteID { Basic, Grayscale };

		/**
		 *  \brief Load image from file to memory
		 *  
		 *  \param [in] filename Path to image file
		 *  \return TRUE on success, FALSE otherwise
		 */
		bool loadFromFile(const std::string &filename);
		
		/**
		 *  \brief Save image to file
		 *  
		 *  \param [in] filename Path to image file
		 *  \return TRUE on success, FALSE otherwise
		 */
		bool saveToFile(const std::string &filename);
		
		/**
		 *  \brief Create new canvas
		 *  
		 *  \param [in] width Width in pixels of canvas
		 *  \param [in] height Height in pixels of canvas
		 *  \return TRUE on success, FALSE otherwise
		 *  
		 *  \details Canvas is filled with values 255, which in
		 *  supported palettes means white.
		 */
		bool create(uint32_t width, uint32_t height);
		
		/**
		 *  \brief Set value of pixel in canvas
		 *  
		 *  \param [in] x X coordinate of pixel
		 *  \param [in] y Y coordinate of pixel
		 *  \param [in] value Value of the pixel
		 *  
		 *  \pre The \ref create method was successfully called prior to
		 *  this method.
		 *  
		 *  \details Make sure the \p x and \p y are within size of the canvas. Canvas
		 *  is indexed from topleft corner, y is incremented downwards.
		 */
		void setPixel(uint32_t x, uint32_t y, uint8_t value);
		
		/**
		 *  \brief Set custom color palette
		 *  
		 *  \param [in] palette Vector of colors
		 *  
		 *  \details Palette *must* have exactly 256 colors. If it has less, the remaining colors will
		 *  be white and if it hase more, it will be cut. The alpha channel must be zero (otherwise)
		 *  you're risking undefined behaviour.
		 */
		void setPalette(const std::vector<bmp::Color> &palette);
		
		/**
		 *  \brief Set predefined color palette
		 *  
		 *  \param [in] id \ref PaletteID identifier of the value
		 */
		void setPalette(PaletteID id);
		
		uint8_t getPixel(uint32_t x, uint32_t y) const { return pixels[y * dibHeader.width + x]; }
		
		uint32_t getWidth() const { return dibHeader.width; }
		
		uint32_t getHeight() const { return dibHeader.height; }
	};
}

#endif
