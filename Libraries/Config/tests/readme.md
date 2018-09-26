# Config - tests

## Introduction

Functionality present in the Config module can be automatically tested and new tests can be added anytime. Refer to this file for info on the subject.

## Running testsuite

In the adjacent directory, use command `make test` to run the testsuite. This command will compile the library, install it (needed), build the testsuite, install it (needed), run the testsuite and then it removes the testsuite binary from the install path.

Above steps are needed since Windows has their dependency search system a bit broken.

Testsuite will run all tests and if any of them fails, it prints all errors related to that test and carry on with evaluating rest of the cases.

## Writing tests

### Adding external files

Please add new files relevant to testing to the tests dir, but when using relative paths, note that current working directory for tests is the library root, so for loading file test0.csv located in tests, one has to use relative path 'tests/test0.csv'.

### Adding new testcase

In file `tests/TestCases.hpp' create new class TestXX (where XX is smallest unused number for the test case), publicly inheriting from TestCase class.

Then implement the pure virtual function `void run()` with your test functionality.

#### Error reporting

As you might have noticed, the run() method has no return value. Instead of that, run() should throw exception whenever neccessary as the testrunner catches any exception and deals with it properly.

Since C/C++ has shitty assert capabilities, whenever you need to use assert, call method assume. If takes two arguments - first is bool (result of your condition) and second is error message that will be displayed if your assume fails. This method will throw an exception whenever the condition is false.

### Registering test case

When your test case class is implemented, open up `tests/main.cpp`. In the main method, you can find vector of TestCases. Simply add your new test case as `new TestXX()`. Now you can run the testsuite and verify your test.