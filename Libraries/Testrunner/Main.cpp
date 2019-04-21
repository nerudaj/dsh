#include "Test.hpp"
#include <vector>

class TestAssertTrue : public Test {
public:
	virtual void run() final override {
		assertTrue(true, "Threw on true");
	}
	
	virtual std::string name() const final override {
		return "TestAssertTrue";
	}
};

class TestAssertFalse : public Test {
public:
	virtual void run() final override {
		assertFalse(false, "Threw on false");
	}
	
	virtual std::string name() const final override {
		return "TestAssertFalse";
	}
};

class TestAssertException : public Test {
public:
	virtual void run() final override {
		std::vector<int> array(10, 0);
		
		assertException({
			array.at(20);
		}, std::out_of_range, "Did not throw out_of_range");
	}
	
	virtual std::string name() const final override {
		return "TestAssertException";
	}
};

class TestAssertNotException : public Test {
public:
	virtual void run() final override {
		std::vector<int> array(10, 0);
		
		assertNotException({
			array.at(9);
		}, "Did throw something");
	}
	
	virtual std::string name() const final override {
		return "TestAssertNotException";
	}
};

int main() {
	Testrunner runner({
		new TestAssertTrue(),
		new TestAssertFalse(),
		new TestAssertException(),
		new TestAssertNotException()
	});
	
	return runner.evaluateTestcases(true);
}