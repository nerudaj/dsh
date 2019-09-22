#include <Test.hpp>
#include <RawHeaders.hpp>
#include <fstream>
#include <IO.hpp>

#include "Comparators.hpp"

class BmpHeaderValidTest : public Test {
public:
	void run() override {
		raw::BmpHeader header(1000);
		assertTrue(header.isValid());
	}
	
	std::string name() const override {
		return "BmpHeaderValidTest";
	}
};

class DibHeaderValidTest : public Test {
public:
	void run() override {
		raw::DibHeader header(10, 100);
		assertTrue(header.isValid8bit());
	}
	
	std::string name() const override {
		return "BmpHeaderValidTest";
	}
};

class IOBmpHeaderTest : public Test {
private:
	std::size_t pixelCount;

public:
	void run() override {
		std::ofstream save("test.bmp", std::ios::binary);
		raw::BmpHeader bmp(pixelCount);
		IO::saveBmpHeaderToStream(bmp, save);
		save.close();
		save.clear();

		std::ifstream load("test.bmp", std::ios::binary);
		raw::BmpHeader ref;
		IO::loadBmpHeaderFromStream(ref, load);
		load.close();
		load.clear();

		assertTrue(bmp == ref);
	}

	std::string name() const override {
		return "IOBmpHeaderTest";
	}

	IOBmpHeaderTest(std::size_t in) : pixelCount(in) {}
};

class IODibHeaderTest : public Test {
private:
	std::uint32_t width, height;

public:
	void run() override {
		std::ofstream save("test.bmp", std::ios::binary);
		raw::DibHeader dib(width, height);
		IO::saveDibHeaderToStream(dib, save);
		save.close();
		save.clear();

		std::ifstream load("test.bmp", std::ios::binary);
		raw::DibHeader ref;
		IO::loadDibHeaderFromStream(ref, load);
		load.close();
		load.clear();

		assertTrue(dib == ref);
	}

	std::string name() const override {
		return "IODibHeaderTest";
	}

	IODibHeaderTest(uint32_t width, uint32_t height) : width(width), height(height) {}
};

class IOPaletteTest : public Test {
public:
	void run() override {
		std::ofstream save("test.bmp", std::ios::binary);
		bmp::Palette pal = bmp::Palette::getGrayscalePalette();
		IO::savePaletteToStream(pal, save);
		save.close();
		save.clear();

		std::ifstream load("test.bmp", std::ios::binary);
		bmp::Palette ref = IO::loadPaletteFromStream(load);
		load.close();
		load.clear();

		assertTrue(pal == ref);
	}
	
	std::string name() const override {
		return "IOPaletteTest";
	}
};

class IOPixelsTest : public Test {
private:
	std::vector<uint8_t> pixels;
	uint32_t width;
	uint32_t height;

public:
	void run() override {
		std::ofstream save("test.bmp", std::ios::binary);
		IO::savePixelsToStream(pixels, width, save);
		save.close();
		save.clear();
		
		std::ifstream load("test.bmp", std::ios::binary);
		std::vector<uint8_t> ref = IO::loadPixelsFromStream(load, width, height);
		load.close();
		load.clear();

		assertTrue(pixels == ref);
	}
	
	std::string name() const override {
		return "IOPixelsTest";
	}
	
	IOPixelsTest(const std::vector<uint8_t> &pixels, uint32_t width, uint32_t height) : pixels(pixels), width(width), height(height) {}
};

class BitmapSaveLoadTest : public Test {
private:
	bmp::Bitmap bmp;

public:
	void run() override {
		bmp.saveToFile("test.bmp");

		bmp::Bitmap ref;
		ref.loadFromFile("test.bmp");

		assertTrue(bmp.getPalette() == ref.getPalette());
		assertTrue(bmp.getWidth() == ref.getWidth());
		assertTrue(bmp.getHeight() == ref.getHeight());

		for (unsigned y = 0; y < bmp.getHeight(); y++) {
			for (unsigned x = 0; x < bmp.getWidth(); x++) {
				inLoop(inLoop(assertTrue(bmp.getPixel(x, y) == ref.getPixel(x, y)), x), y);
			}
		}
	}

	std::string name() const override {
		return "BitmapSaveLoadTest";
	}

	BitmapSaveLoadTest() {
		bmp.create(100, 100);
		bmp.setPalette(bmp::Palette::getUnixPalette());

		for (unsigned y = 0; y < 100; y++) {
			for (unsigned x = 0; x < 100; x++) {
				bmp.setPixel(x, y, (y * 100 + x) % 256);
			}
		}
	}
};

int main(int argc, char *argv[]) {
	Testrunner runner({
		new BmpHeaderValidTest(),
		new DibHeaderValidTest(),
		new IOBmpHeaderTest(0),
		new IOBmpHeaderTest(1000),
		new IODibHeaderTest(0, 0),
		new IODibHeaderTest(10, 0),
		new IODibHeaderTest(4, 4),
		new IODibHeaderTest(10, 10),
		new IOPaletteTest(),
		new IOPixelsTest({}, 0, 0),
		new IOPixelsTest({0, 1, 2, 3}, 2, 2),
		new IOPixelsTest({0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15}, 4, 4),
		new BitmapSaveLoadTest()
	});
	
	return runner.evaluateTestcases(true);
}