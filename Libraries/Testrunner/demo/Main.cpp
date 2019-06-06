#include <Test.hpp>
#include <vector>

class TestAssertTrue : public Test {
public:
	virtual void run() final override {
		assertTrue(true); // Try changing it to false
	}
	
	virtual std::string name() const final override {
		return "TestAssertTrue";
	}
};

class TestAssertFalse : public Test {
public:
	virtual void run() final override {
		assertFalse(false); // Try changing it to true
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
			array.at(20); // Try changing it to 9
		}, std::out_of_range);
	}
	
	virtual std::string name() const final override {
		return "TestAssertException";
	}
};

class TestAssertExceptionWithMsg : public Test {
public:
	virtual void run() final override {
		std::vector<int> array(10, 0);

		assertExceptionWithMessage({
			array.at(20); // Try changing it to 9
		}, std::out_of_range, "vector::_M_range_check: __n (which is 20) >= this->size() (which is 10)");
	}

	virtual std::string name() const final override {
		return "TestAssertExceptionWithMessage";
	}
};

class TestAssertNotException : public Test {
public:
	virtual void run() final override {
		std::vector<int> array(10, 0);
		
		assertNotException({
			array.at(9); // Try changing it to 20
		});
	}
	
	virtual std::string name() const final override {
		return "TestAssertNotException";
	}
};

class TestAssertEqual : public Test {
public:
	virtual void run() final override {
		// Try changing value of any of these variables!
		int a = 10;
		int b = 10;
		assertEqual(a, b, std::to_string(a), std::to_string(b));
	}
	
	virtual std::string name() const final override {
		return "TestAssertEqual";
	}
};

class TestAssertNotEqual : public Test {
public:
	virtual void run() final override {
		// Try changing value of any of these variables!
		int a = 10;
		int b = 20;
		assertNotEqual(a, b, std::to_string(a), std::to_string(b));
	}
	
	virtual std::string name() const final override {
		return "TestAssertNotEqual";
	}
};


class TestInLoop : public Test {
public:
	virtual void run() final override {
		// Try changing number of values in array or value of any item!
		std::vector<int> array({ 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 });

		assertEqual(array.size(), 10, std::to_string(array.size()), "10");
		for (unsigned i = 0; i < array.size(); i++) {
			inLoop(assertEqual(array[i], i, std::to_string(array[i]), std::to_string(i)), i);
		}
	}
	
	virtual std::string name() const final override {
		return "TestInLoop";
	}
};

int main() {
	Testrunner runner({
		new TestAssertTrue(),
		new TestAssertFalse(),
		new TestAssertException(),
		new TestAssertExceptionWithMsg(),
		new TestAssertNotException(),
		new TestAssertEqual(),
		new TestAssertNotEqual(),
		new TestInLoop(),
	});
	
	return runner.evaluateTestcases(true);
}