#include "LevelD.hpp"
#include "Test.hpp"
#include <iostream>
#include <Config.hpp>

using std::string;
using std::vector;

void assume(bool cond, const std::string &str) {
    if (!cond) throw std::runtime_error(str);
}

void printHelp(const std::string &programName);

int main(int argc, char *argv[]) {
    cfg::Args args("hs");
    try {
        args.parse(argc, argv);
    } catch (...) {
        printHelp(argv[1]);
        return 1;
    }

    if (args.isSet('h')) {
        printHelp(argv[1]);
        return 0;
    }

    vector<Test*> tests = {
        new TestMetadata({}),
        new TestMetadata({{"map01", "Hangar", "doomista", "dsc", 10}, {}, {}, {}, {}}),
        new TestMesh({}),
        new TestMesh({{}, {2, 2, {1, 2, 3, 4}, {1, 0, 0, 1}}, {}, {}, {}}),
        new TestPlayers({}),
        new TestPlayers({{}, {}, {
            {1, 2, 0}, {10, 20, 30}, {244, 300, 10}
        }, {}, {}}),
        new TestItems({}),
        new TestItems({{}, {}, {}, {
            {1, 2, 0}, {10, 20, 30}, {244, 300, 10}
        }, {}}),
        new TestNpcs({}),
        new TestNpcs({{}, {}, {}, {}, {
            {1, 2, 0}, {10, 20, 30}, {244, 300, 10}
        }}),
        new TestAll({
            { "MAP01", "Entryway", "doomista", "First level of the game", 1554812963 },
            { 4, 4,
                { 1, 2, 2, 3, 
                  2, 0, 0, 2, 
                  2, 0, 0, 2, 
                  4, 2, 2, 5 }, 
                { 1, 1, 1, 1, 
                  1, 0, 0, 1, 
                  1, 0, 0, 1, 
                  1, 1, 1, 1} },
            { {64, 128, 0} },
            { {192, 192, 1} },
            { {128, 64, 10}, {192, 192, 1} }
        })
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

    if (args.isSet('s')) {
        std::cout << std::endl;
        std::cout << "SUMMARY:" << std::endl;
        std::cout << "Total  : " << cnt << std::endl;
        std::cout << "Passed : " << success << std::endl;
        std::cout << "Failed : " << failure << std::endl;
    }

    return failure;
}

void printHelp(const std::string &programName) {
    std::cout << "Usage:" << std::endl;
    std::cout << "\t" << programName << " [-h] [-s]" << std::endl;
    std::cout << std::endl;

    std::cout << "Parameters:" << std::endl;
    vector<std::pair<string, string>> params = {
        {"-h", "Prints help" },
        {"-s", "Print test summary"}
    };

    for (auto &param : params) {
        std::cout << "\t" << param.first << "  " << param.second << std::endl;
    }

    std::cout << std::endl;
}