#include <iostream>
#include "TestCases.hpp"
#include "../Config.hpp"

int main() {
	std::vector<TestCase*> cases = {
		new TestLoadValidCSV("tests/test0.csv"),
		new TestLoadValidCSV("tests/test1.csv"),
		new TestLoadValidCSV("tests/test2.csv"),
		new TestLoadValidCSV("tests/test3.csv"),
		new TestLoadValidCSV("tests/test4.csv"),
		new TestLoadValidCSV("tests/test5.csv"),
		new TestValidCSVData("tests/test0.csv", {
			{"aaa", "bbb", "ccc"}, { "ddd", "eee", "fff" }
		}),
		new TestValidCSVData("tests/test1.csv", {
			{"aaa", "bbb", "ccc"}, { "ddd", "eee", "fff" }
		}),
		new TestValidCSVData("tests/test2.csv", {
			{"aaa", "bbb", "cc\nc"}, { "ddd", "eee", "fff" }
		}),
		new TestValidCSVData("tests/test3.csv", {
			{"aaa", "bbb", "cc,c"}, { "ddd", "eee", "fff" }
		}),
		new TestValidCSVData("tests/test4.csv", {
			{"aaa", "bbb", "cc\"c"}, { "ddd", "eee", "fff" }
		}),
	};

	int cnt = 1;
	for (auto test : cases) {
		std::cout << "TEST " << cnt << "/" << cases.size() << " - " << test->name() << "\n";

		try {
			test->run();
			std::cout << "[OK]\n";
		}
		catch (std::exception &e) {
			std::cout << "Exception occured: " << e.what() << "\n";
		}

		delete test;
		cnt++;
	}

	return 0;
}