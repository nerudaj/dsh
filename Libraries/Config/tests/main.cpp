#include <iostream>
#include "TestCases.hpp"
#include "../Config.hpp"

int main() {
	std::vector<TestCase*> cases = {
		new TestLoadValidCSV("tests/test0.csv"),
		new TestLoadValidCSV("tests/test1.csv"),
		new TestLoadValidCSV("tests/test2.csv"),
		new TestLoadValidCSV("tests/test3.csv")
	};

	int cnt = 1;
	for (auto test : cases) {
		std::cout << "TEST " << cnt << "/" << cases.size() << "\n";

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