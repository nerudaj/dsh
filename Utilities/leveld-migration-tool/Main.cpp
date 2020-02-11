#include <iostream>
#include <Config.hpp>
#include <LevelD.hpp>

void printHelp() {
    std::cout << "Usage:" << std::endl;
    std::cout << "\tleveld-migration-tool [-h] | <-i filename> <-o filename>" << std::endl;
    std::cout << std::endl;
    
    std::cout << "Parameters:" << std::endl;
    std::cout << "\t-h            Prints this message" << std::endl;
    std::cout << "\t-i filename   Input file" << std::endl;
    std::cout << "\t-o filename   Output file" << std::endl;
    
    std::cout << std::endl;
    std::cout << "Description:" << std::endl;
    std::cout << "\tThis tool is meant for converting .lvd files with obsolete versions into .lvd with current version." << std::endl;
    std::cout << std::endl;
}

int main(int argc, char *argv[]) {
    cfg::Args args("hi:o:");
    
    try { args.parse(argc, argv); }
    catch (std::exception &e) {
        std::cerr << "ERROR: " << e.what() << std::endl;
    }
    
    if (args.isSet('h')) {
        printHelp();
        return 0;
    }
    
    if (!args.isSet('i')) {
        std::cerr << "ERROR: Parameter -i is mandatory!" << std::endl;
        return 1;
    }
    
    if (!args.isSet('o')) {
        std::cerr << "ERROR: Parameter -o is mandatory!" << std::endl;
        return 1;
    }

    try {
        LevelD lvld;
        lvld.loadFromFile(args.getArgumentValue('i').asString());
        lvld.saveToFile(args.getArgumentValue('o').asString());
    } catch (std::exception &e) {
        std::cerr << "ERROR: " << e.what() << std::endl;
    }

    return 0;
}