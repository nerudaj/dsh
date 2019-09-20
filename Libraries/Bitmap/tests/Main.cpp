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
public:
	void run() override {
		throw std::runtime_error("Not implemented!");
	}
	
	std::string name() const override {
		return "IOPixelsTest";
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
		new IOPixelsTest(),
	});
	
	return runner.evaluateTestcases(true);
}