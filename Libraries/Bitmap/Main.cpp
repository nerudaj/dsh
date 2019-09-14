#include "Bitmap.hpp"

int main() {
    bmp::Bitmap bitmap;
    /*bitmap.create(128, 128);
    bitmap.saveToFile("pokus.bmp");

    bitmap.create(16,16);
    uint8_t i = 0;
    for (unsigned y = 0; y < 16u; y++) {
        for (unsigned x = 0; x < 16u; x++) {
            bitmap.setPixel(x, y, i++);
        }
    }
    bitmap.saveToFile("pokus2.bmp");
    
    bitmap.resize(1024, 1024);*/
    //bitmap.setPalette(bmp::Palette::getUnixPalette());
    //bitmap.saveToFile("pokus3.bmp");

    bitmap.create(2, 2);
    bitmap.setPixel(0, 0, 0);
    bitmap.setPixel(1, 0, 96);
    bitmap.setPixel(0, 1, 192);
    bitmap.setPixel(1, 1, 255);
    bitmap.saveToFile("resize0.bmp");
    bitmap.resize(128, 128);
    bitmap.saveToFile("resize1.bmp");
    bitmap.resize(71, 71);
    bitmap.saveToFile("resize2.bmp");

    return 0;
}