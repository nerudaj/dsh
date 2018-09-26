#pragma once

#include <string>
#include <cassert>
#include "../Config.hpp"

class TestCase {
private:
	std::string data;

public:
	void assume(bool condition, const std::string &message) {
		if (!condition) throw std::runtime_error(message);
	}

	virtual void run() =0;

	TestCase() {}
	TestCase(const std::string &context) { data = context; }
	virtual ~TestCase() {}
};

class Test0 : public TestCase {
public:
	virtual void run() final override {
		cfg::Csv csv;
		assume(csv.loadFromFile("test0.csv", int(cfg::Csv::Flags::NoHeaders)), "CSV did not loaded file test0.csv correctly");
		assume(csv.getSize() == 2, "Number of rows should have been 2");
		
		/*for (auto row = csv.begin(); row != csv.end(); row++) {
			assume(row.size() == 3, "Size of each row should be 3");
		}*/
		for (auto row : csv) {
			assume(row.size() == 3, "Size of each row should be 3");
		}
	}
};
