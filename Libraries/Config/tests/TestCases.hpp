#pragma once

#include <string>
#include <vector>
#include "../Config.hpp"

/**
 *  \brief Base class for deriving test cases from
 */
class TestCase {
public:
	/**
	 *  \brief Advanced replacement for assert
	 *  
	 *  \param [in] condition Result of bool operation
	 *  \param [in] message Message that will be displayed if \p condition is false
	 *  
	 *  \details If condition is false, then an exception is thrown
	 */
	void assume(bool condition, const std::string &message) {
		if (!condition) throw std::runtime_error(message);
	}

	/**
	 *  \brief Main code of test
	 *  
	 *  \details Implement this function in your derived class - this is the main logic of your test. Use \ref assume whenever applicable.
	 */
	virtual void run() =0;

	/**
	 *  \brief Get name of the test case
	 *  
	 *  \return Copy of name string
	 *  
	 *  \details Implement this function in your derived class. This function is used to make testing output more comprehensive. Usual format of this string is: NameOfTheClass(important,parameters)
	 */
	virtual std::string name() const = 0;

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
		assume(csv.size() == 2, "Number of rows should have been 2");

		int cnt = 0;
		for (auto row : csv) {
			assume(row.size() == 3, "Size of row " + std::to_string(cnt) + " should be 3, but is " + std::to_string(row.size()));
			cnt++;
		}
	}
	
	virtual std::string name() const final override {
		return "TestLoadValidCSV(" + data + ")";
	}

	TestLoadValidCSV(const std::string &filename) { data = filename; }
};

class TestValidCSVData : public TestCase {
protected:
	std::string data;
	const std::vector<std::vector<std::string>> refValues;

public:
	virtual void run() final override {
		cfg::Csv csv;
		assume(csv.loadFromFile(data, int(cfg::Csv::Flags::NoHeaders)), "CSV did not loaded file " + data + " correctly");
		
		assume(csv.size() == refValues.size(), "Number of rows in csv does not match referenceValues");
		
		for (unsigned i = 0; i < csv.size(); i++) {
			assume(csv[i].size() == refValues[i].size(), "Number of columns on row " + std::to_string(i) + " in csv (" + std::to_string(csv[i].size()) + ") does not match reference data (" + std::to_string(refValues[i].size()) + ").");
			
			for (unsigned p = 0; p < csv[i].size(); p++) {
				assume(csv[i][p].asString() == refValues[i][p], "Value '" + csv[i][p].asString() + "' from csv does not match '" + refValues[i][p] + "' from reference data.");
			}
		}
	}

	virtual std::string name() const final override {
		return "TestValidCSVData(" + data + ")";
	}

	TestValidCSVData(const std::string &filename, const std::vector<std::vector<std::string>> &correctValues) : refValues(correctValues) { data = filename; }
};