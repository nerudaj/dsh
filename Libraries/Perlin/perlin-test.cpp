#include <Perlin.hpp>
#include <Bitmap.hpp>
#include <iostream>

const unsigned W = 100;
const unsigned H = 100;

int main() {
	bmp::Bitmap image;
	image.create(W, H);
	
	perlin::NoiseGenerator<2> noise;
	noise.setGradientGridSize({10, 10});
	noise.setGradientGridDensity({10, 10});

	for (int y = 0; y < H; y++) {
		for (int x = 0; x < W; x++) {
			float value = noise.getValueAt({x, y});
			std::cout << value << std::endl;
			value += 2.f;
			int val = static_cast<int>(value * 255.f / 4.f) / 10;
			image.setPixel(x, y, val * 10);
		}
	}
	
	image.saveToFile("noise.bmp");
	return 0;
}