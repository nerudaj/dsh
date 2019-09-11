#include "Bitmap.hpp"

int main() {
    bmp::Bitmap bitmap;
    bitmap.create(128, 128);
    bitmap.saveToFile("pokus.bmp");
    return 0;
}