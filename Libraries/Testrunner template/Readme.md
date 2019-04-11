# Testrunner template

This folder contain template for making testrunners for your libraries.

## How to use

If you set `tests` property in your Makefile.in to true, `makegen` will generate test target for your library. To use it properly, create new folder called `tests` in your library folder and copy `main.cpp` from this folder to your new test folder.

After that, you can call `make test` which will compile your library, create testrunner binary and run it.

## How to write tests

This is simple. In the `main.cpp` you can find TestCase virtual class. All of your testcases must inherit from this class and implement run and name behaviours. Name is simple string that will help you identify your testcase among others.

Run is simply body of your testcase. Load any input files here (keep in mind that testrunner binary is run from folder above `tests`) and use assume function for evaluating conditions.

Assume function takes two arguments - bool (condition) and string (message). If first argument is evaluated to false, assume will throw exception with message as a text that will get printed to console. This is somewhat upgraded assert.

If run function finishes without throwing any kind of exception, the test is considered as a pass.