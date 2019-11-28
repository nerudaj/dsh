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
 * \brief Expect condition to be true
 *  
 * \param[in]  c  Condition to evaluate
 *
 * Throws an exception if condition is false
 */
#define assertTrue(c) if (!(c)) throw std::runtime_error("Assertion failed: " + std::string(#c) + " is false (expected true).");

/**
 * \brief Expect condition to be false
 *  
 * \param[in]  c  Condition to evaluate
 * 
 * Throws an exception if condition is true
 */
#define assertFalse(c) if (c) throw std::runtime_error("Assertion failed: " + std::string(#c) + " is true (expected false).");

/**
 * \brief Expect two values to have the same value
 *
 * \param[in]  a    First value to compare
 * \param[in]  b    Second value to compare
 * \param[in] aStr  Parameter \p a serialized to string
 * \param[in] bStr  Parameter \p b serialized to string
 *
 * Parameters \p a and \p b must be comparable using != operator.
 * Throws an exception if parameters have different values from 
 * each other.
 */
#define assertEqual(a,b,aStr,bStr) if ((a) != (b)) throw std::runtime_error("Assertion failed: " + std::string(#a) + " == " + #b + ".\n" + std::string(#a) + " = " + aStr + "\n" + std::string(#b) + " = " + bStr);

#define assertEqualStrCompat(a, b) if ((a) != (b)) throw std::runtime_error("Assertion failed: " + std::string(#a) + " == " + #b + ".\n" + std::string(#a) + " = " + std::to_string(a) + "\n" + std::string(#b) + " = " + std::to_string(b));

/**
 * \brief Expect two values to have different values
 *
 * \param[in]  a    First value to compare
 * \param[in]  b    Second value to compare
 * \param[in] aStr  Parameter \p a serialized to string
 * \param[in] bStr  Parameter \p b serialized to string
 *
 * Parameters \p a and \p b must be comparable using == operator.
 * Throws an exception if parameters have the same value.
 */
#define assertNotEqual(a,b,aStr,bStr) if ((a) == (b)) throw std::runtime_error("Assertion failed: " + std::string(#a) + " != " + #b + ".\n" + std::string(#a) + " = " + aStr + "\n" + std::string(#b) + " = " + bStr);

/**
 * \brief Print loop control variable if assertion fails
 *
 * \param[in]  asrt        Assertion to evaluate
 * \param[in]  controlVar  Control variable of a loop. Must be 
 * serializable to string using std::to_string
 *
 * If \p asrt fails and throws the exception, then inLoop
 * catches that exception, adds value of \p controlVar to
 * it and then rethrows.
 *
 * \code inLoop(assertTrue(predicate[i]), i); \endcode
 */
#define inLoop(asrt,controlVar) {\
	try { \
		asrt; \
	} catch (std::runtime_error &e) { \
		throw std::runtime_error(std::string(e.what()) + "\n(loop control) " + std::string(#controlVar) + " = " + std::to_string(controlVar)); \
	} \
}

/**
 *  \brief Expect code to throw specific exception
 *  
 *  \param[in] code Code to execute
 *  \param[in] exc Expected exception
 *
 * Throws an exception if exception was either not
 * thrown or different than expected exception was
 * thrown.
 */
#define assertException(code,exc) \
{ \
	bool exceptionHappened = false; \
	try { \
		code; \
	} catch (exc &e) { \
		exceptionHappened = true; \
	} catch (std::exception &e) { \
		std::runtime_error("Assertion failed: Incorrect exception was thrown\nMessage = " + std::string(e.what())); \
	} \
	if (!exceptionHappened) throw std::runtime_error("Assertion failed: Exception " + std::string(#exc) + " was not thrown."); \
}

/**
 *  \brief Expect code to throw specific exception
 *  
 *  \param[in] code Code to execture
 *  \param[in] exp  Expected exception
 *  \param[in] msg  Expected exception message (std::string)
 * 
 *  Throws an exception if exception was either not
 *  thrown or different than expected or with different
 *  message than expected.
 */
#define assertExceptionWithMessage(code, exc, msg) \
{ \
    bool exceptionHappened = false; \
    try { \
        code; \
    } catch (exc &e) { \
        exceptionHappened = true; \
        assertEqual(std::string(e.what()), msg, std::string(e.what()), msg); \
    } catch (std::exception &e) { \
        std::runtime_error("Assertion failed: Incorrect exception was thrown\nMessage = " + std::string(e.what())); \
    } \
    if (!exceptionHappened) throw std::runtime_error("Assertion failed: Exception " + std::string(#exc) + " was not thrown."); \
} 

/**
 * \brief Expect code to not throw any exception
 *  
 * \param[in]  code  Code to execute
 *
 * Throws an exception if the \p code did not throw
 * any exception.
 */
#define assertNotException(code) \
{ \
	try { \
		code; \
	} catch (std::exception &e) { \
		throw std::runtime_error("Assertion failed: An exception was thrown\nMessage = " + std::string(e.what())); \
	} \
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
	
	/**
	 *  \brief Bind vector of testcases to testrunner
	 *  
	 *  All testcases will be properly dealocated either by calling
	 *  \ref clear() or by Testrunner's dtor.
	 */
	void initializeTestVector(const std::vector<Test*> &testcases) {
		Testrunner::testcases = testcases;
	}
	
	/**
	 *  \brief Properly deallocate vector of testcases
	 *  
	 *  After call to this function, new vector of testcases
	 *  can be bind using \ref initializeTestVector
	 */
	void clear() {
		for (auto test : testcases) {
			delete test;
		}
		testcases.clear();
	}
	
public:
	Testrunner(const std::vector<Test*> &testcases) {
		initializeTestVector(testcases);
	}
	
	~Testrunner() {
		clear();
	}
	
	/**
	 *  \brief Evaluate whole vector of test cases
	 *  
	 *  \param[in]  printSummary        Whether brief summary of testing should be printed
	 *  \param[in]  breakAtFirstFailed  Whether tests should end on first failed. Summary won't be printed in that case
	 *  \return Number of failed tests
	 *  
	 *  For each test, its index number and name will be printed, then the
	 *  run() method of that test is executed. If it fails (throws an exception),
	 *  message of this exception will be printed.
	 */
	int evaluateTestcases(bool printSummary = true, bool breakAtFirstFailed = false) {
		int testIndex = 1, succeeded = 0, failed = 0;
		for (auto test : testcases) {
			std::cout << "Test " << testIndex << "/" << testcases.size() << ": " << test->name() << std::endl;
			try {
				test->run();
				std::cout << "[OK]" << std::endl;
				succeeded++;
			}
			catch (std::exception &e) {
				std::cout << "[ERROR]: " << e.what() << std::endl << std::endl;
				failed++;
				
				if (breakAtFirstFailed) return 1;
			}
			
			testIndex++;
		}
		
		if (printSummary) {
			printSummaryText(succeeded, failed);
		}
		
		return failed;
	}
};