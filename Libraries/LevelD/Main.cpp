#include "LevelD.hpp"
#include "Tests/Test.hpp"
#include <iostream>

using std::string;
using std::vector;

void assume(bool cond, const std::string &str) {
    if (!cond) throw std::runtime_error(str);
}

int main(int argc, char *argv[]) {
    vector<Test*> tests = {
        new TestMetadata({}),
        new TestMetadata({{"map01", "Hangar", "doomista", "dsc", 10}, {}, {}, {}}),
        new TestMesh({}),
        new TestMesh({{}, {2, 2, {1, 2, 3, 4}, {1, 0, 0, 1}}, {}, {}}),
        new TestPlayers({}),
        new TestPlayers({{}, {}, {
            {1, 2, 0}, {10, 20, 30}, {244, 300, 10}
        }, {}}),
        new TestItems({}),
        new TestItems({{}, {}, {
            {1, 2, 0}, {10, 20, 30}, {244, 300, 10}
        }, {}})
    };

    unsigned success = 0, failure = 0, cnt = 0;
    for (auto &test : tests) {
        std::cout << "Test " << ++cnt << ": " << test->name() << std::endl;

        try {
            test->run();
            std::cout << "OK" << std::endl;
            success++;
        }
        catch (std::exception &e) {
            std::cout << "ERROR: " << e.what() << std::endl;
            failure++;
        }
    }

    std::cout << std::endl;
    std::cout << "SUMMARY:" << std::endl;
    std::cout << "Total  : " << cnt << std::endl;
    std::cout << "Passed : " << success << std::endl;
    std::cout << "Failed : " << failure << std::endl;

    return failure;
}