#pragma once

#include <string>
#include <stdexcept>
#include <vector>
#include <iostream>

/**
 *  \brief Class for deriving test cases from
 */
class Test {
public:
	/**
	 *  \brief Behaviour of the test
	 *  
	 *  \return None if test passes, an exception on fail
	 *  
	 *  \details When implementing behaviour of the test,
	 *  use macros \ref assertTrue, assertFalse, assertException 
	 *  and assertNotException to check for various conditions.
	 */
	virtual void run() = 0;
	
	/**
	 *  \brief Get informational name of the test
	 */
	virtual std::string name() const = 0;
	virtual ~Test() {}
};

/**
 *  \brief Expect condition to be true
 *  
 *  \param [in] c Condition to evaluate
 *  \param [in] m Descriptive message for exception
 *  \return Throws an exception if condition is false
 */
#define assertTrue(c,m) if (!(c)) throw std::runtime_error(m);

/**
 *  \brief Expect condition to be false
 *  
 *  \param [in] c Condition to evaluate
 *  \param [in] m Descriptive message for exception
 *  \return Throws an exception if condition is true
 */
#define assertFalse(c,m) if (c) throw std::runtime_error(m);

/**
 *  \brief Expect code to throw specific exception
 *  
 *  \param [in] code Code to execute
 *  \param [in] exc Expected exception
 *  \param [in] m Descriptive message for output exception
 *  \return Throws an exception with message \p m if \p code
 *  did not throw an exception of type \p exc
 */
#define assertException(code,exc,m) \
{ \
	bool exceptionHappened = false; \
	try { \
		code; \
	} catch (exc &e) { \
		exceptionHappened = true; \
	} \
	if (!exceptionHappened) throw std::runtime_error(m); \
}

/**
 *  \brief Expect code to not throw any exception
 *  
 *  \param [in] code Code to execute
 *  \param [in] m Descriptive message for output exception
 *  \return Throws an exception with message \p m if \p code
 *  threw an exception of type \p exc
 */
#define assertNotException(code,m) \
{ \
	bool exceptionHappened = false; \
	try { \
		code; \
	} catch (...) { \
		exceptionHappened = true; \
	} \
	if (exceptionHappened) throw std::runtime_error(m); \
}

class Testrunner {
private:
	std::vector<Test*> testcases;
	
	void printSummaryText(int succeeded, int failed) {
		std::cout << std::endl;
		std::cout << "[SUMMARY]" << std::endl;
		std::cout << testcases.size() << " tests were run." << std::endl;
		std::cout << succeeded << " tests succeeded." << std::endl;
		std::cout << failed << " tests failed." << std::endl;
	}
	
public:
	Testrunner(const std::vector<Test*> &testcases) {
		initializeTestVector(testcases);
	}
	
	~Testrunner() {
		clear();
	}
	
	/**
	 *  \brief Bind vector of testcases to testrunner
	 *  
	 *  \details All testcases will be properly dealocated either by calling
	 *  \ref clear() or by Testrunner's dtor.
	 */
	void initializeTestVector(const std::vector<Test*> &testcases) {
		Testrunner::testcases = testcases;
	}
	
	/**
	 *  \brief Properly deallocate vector of testcases
	 *  
	 *  \details After call to this function, new vector of testcases
	 *  can be bind using \ref initializeTestVector
	 */
	void clear() {
		for (auto test : testcases) {
			delete test;
		}
		testcases.clear();
	}
	
	/**
	 *  \brief Evaluate whole vector of test cases
	 *  
	 *  \param [in] printSummary Whether brief summary of testing should be printed
	 *  \return Number of failed tests
	 *  
	 *  \details For each test, its index number and name will be printed, then the
	 *  run() method of that test is executed. If it fails (throws an exception),
	 *  message of this exception will be printed.
	 */
	int evaluateTestcases(bool printSummary) {
		int testIndex = 1, succeeded = 0, failed = 0;
		for (auto test : testcases) {
			std::cout << "Test " << testIndex << "/" << testcases.size() << ": " << test->name() << std::endl;
			try {
				test->run();
				std::cout << "[OK]" << std::endl;
				succeeded++;
			}
			catch (std::exception &e) {
				std::cout << "[ERROR]: " << e.what() << std::endl;
				failed++;
			}
			
			testIndex++;
		}
		
		if (printSummary) {
			printSummaryText(succeeded, failed);
		}
		
		return failed;
	}
};