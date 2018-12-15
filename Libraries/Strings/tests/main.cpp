#include <stdexcept>
#include <string>
#include <vector>
#include <Strings.hpp>

using std::string;
using std::vector;
using std::cout;
using std::endl;

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
	void assume(bool condition, const string &message) {
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
	virtual string name() const = 0;

	TestCase() {}
	virtual ~TestCase() {}
};

class TestReplaceAll : public TestCase {
protected:
	string input, from, to;
	string ref;
	
public:
	virtual void run() final override {
		Strings::replaceAll(input, from, to);
		assume(input == ref, 
			"Value mismatch, expected '" + ref + 
			"' but got '" + input + "'"
		);
	}
	
	virtual string name() const final override {
		return "TestReplaceAll";
	}
	
	TestReplaceAll(const string &in, const string &fromstr, const string &tosstr, const string &refout) : input(in), from(fromstr), to(tosstr), ref(refout) {}
};

int main() {
	vector<TestCase*> testcases = {
		new TestReplaceAll("aaa", "", "", "aaa"),
		new TestReplaceAll("", "a", "b", ""),
		new TestReplaceAll("aaa", "a", "aa", "aaaaaa"),
		new TestReplaceAll("abc", "bc", "aa", "aaa")
	};
	
	int cnt = 1;
	int failed = 0, succeeded = 0;
	for (auto test : testcases) {
		cout << "TEST " << cnt << "/" << testcases.size() << " - " << test->name() << endl;
		
		try {
			test->run();
			cout << "[OK]" << endl;
			succeeded++;
		}
		catch (std::exception &e) {
			cout << "[ERROR] " << e.what() << "\n";
			failed++;
		}
		
		delete test;
		cnt++;
	}
	
	cout << endl;
	cout << "[SUMMARY]" << endl;
	cout << testcases.size() << " tests were run." << endl;
	cout << succeeded << " tests succeeded." << endl;
	cout << failed << " tests failed." << endl;
	
	return failed;
}