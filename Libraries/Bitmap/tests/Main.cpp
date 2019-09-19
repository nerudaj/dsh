#include <Test.hpp>
#include <RawHeaders.hpp>

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

int main(int argc, char *argv[]) {
	Testrunner runner({
		new BmpHeaderValidTest(),
		new DibHeaderValidTest()
	});
	
	return runner.evaluateTestcases(true);
}