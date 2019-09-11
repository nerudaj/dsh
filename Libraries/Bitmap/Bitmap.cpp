#include "Bitmap.hpp"

void bmp::Bitmap::create(unsigned width, unsigned height) {
    data.resize(width * height, 0);
    bmp::Bitmap::width = width;
    bmp::Bitmap::height = height;
}

bmp::Bitmap::Bitmap() {
    width = 0;
    height = 0;
    palette = bmp::Palette::getGrayscalePalette();
}