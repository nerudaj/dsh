#pragma once

#include "Bitmap.hpp"
#include <cstdint>

namespace raw {
    #pragma pack(1)
    struct Color {
        uint8_t red;
        uint8_t green;
        uint8_t blue;
        uint8_t alpha;

        bmp::Color toBmpColor() const {
            return bmp::Color(red, green, blue);
        }

        Color() {}
        Color(const bmp::Color &color) {
            red = color.red;
            green = color.green;
            blue = color.blue;
            alpha = 0;
        }
    };

    struct BmpHeader {
        uint16_t identity; ///< String "BM"
        uint32_t sizeOfFile; ///< size of file (headers + data)
        uint16_t reserved1; ///< 0x0000
        uint16_t reserved2; ///< 0x0000
        uint32_t dataOffset; ///< SIZEOF(bmpheader) + sizeof(dibheader) + palette

        bool isValid() const;

        BmpHeader() {}
        BmpHeader(size_t pixelCount);
    };

    struct DibHeader {
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

        DibHeader() {}
        DibHeader(uint32_t width, uint32_t height);

        bool isValid8bit() const;
    };
    #pragma pack()
}
