#pragma once

#include <string>
#include <cassert>
#include "../Config.hpp"

class TestCase {
public:
	void assume(bool condition, const std::string &message) {
		if (!condition) throw std::runtime_error(message);
	}

	virtual void run() =0;

	TestCase() {}
	virtual ~TestCase() {}
};

class TestLoadValidCSV : public TestCase {
protected:
	std::string data;

public:
	virtual void run() final override {
		cfg::Csv csv;
		assume(csv.loadFromFile(data, int(cfg::Csv::Flags::NoHeaders)), "CSV did not loaded file " + data + " correctly");
		assume(csv.getSize() == 2, "Number of rows should have been 2");
		
		/*for (auto row = csv.begin(); row != csv.end(); row++) {
			assume(row.size() == 3, "Size of each row should be 3");
		}*/
		int cnt = 0;
		for (auto row : csv) {
			assume(row.size() == 3, "Size of row " + std::to_string(cnt) + " should be 3, but is " + std::to_string(row.size()));
			cnt++;
		}
	}
	
	TestLoadValidCSV(const std::string &filename) { data = filename; }
};
