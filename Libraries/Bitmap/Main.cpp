#include "Bitmap.hpp"

int main() {
    bmp::Bitmap bitmap;
    bitmap.create(128, 128);
    bitmap.saveToFile("pokus.bmp");

    bmp::Bitmap bitmap2;
    bitmap.create(16,16);
    uint8_t i = 0;
    for (unsigned y = 0; y < 16u; y++) {
        for (unsigned x = 0; x < 16u; x++) {
            bitmap.setPixel(x, y, i++);
        }
    }
    bitmap.saveToFile("pokus2.bmp");

    return 0;
}