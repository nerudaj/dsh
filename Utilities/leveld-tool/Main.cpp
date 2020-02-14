#include <iostream>
#include <fstream>
#include <Strings.hpp>
#include <Config.hpp>
#include <LevelD.hpp>

void printHelp() {
    std::cout << "Usage:" << std::endl;
    std::cout << "\tleveld-tool [-h] | <-i file> [-m outfile [-e str]]" << std::endl;
    std::cout << std::endl;
    
    std::cout << "Parameters:" << std::endl;
    std::cout << "\t-h            Prints this message" << std::endl;
    std::cout << "\t-f file       Input file" << std::endl;
    std::cout << "\t-m outfile    Migrate input file version to newest as save it as outfile" << std::endl;
    std::cout << "\t-e str        Edit metadata item. Str is key=value pair, see below" << std::endl;

    std::cout << std::endl;
    std::cout << "Description:" << std::endl;
    std::cout << "\tBy default, this tool prints info about .lvd files. If -m was specified, it migrates input file to newest version of LevelD file format." << std::endl;
    std::cout << "\tWhen using -e option, the str is in key=value format, where key is name of metadata attribute and value is the new value. For example: -e \"author=Example Author\". You can overwrite the input file." << std::endl;
    std::cout << std::endl;
}

void printInfo(const LevelD &lvd, uint16_t version) {
    std::cout << "Version:       " << version << std::endl;

    std::cout << std::endl;
    std::cout << "Metadata:" << std::endl;
    std::cout << "\tTimestamp:   " << lvd.metadata.timestamp << std::endl;
    std::cout << "\tId:          " << lvd.metadata.id << std::endl;
    std::cout << "\tAuthor:      " << lvd.metadata.author << std::endl;
    std::cout << "\tName:        " << lvd.metadata.name << std::endl;
    std::cout << "\tDescription: " << lvd.metadata.description << std::endl;

    std::cout << std::endl;
    std::cout << "Mesh:" << std::endl;
    std::cout << "\ttileWidth:   " << lvd.mesh.tileWidth << std::endl;
    std::cout << "\ttileHeight:  " << lvd.mesh.tileHeight << std::endl;
    std::cout << "\twidth:       " << lvd.mesh.width << std::endl;
    std::cout << "\theight:      " << lvd.mesh.height << std::endl;

    std::cout << std::endl;
    std::cout << "Number of player spawns: " << lvd.players.size() << std::endl;
    std::cout << "Number of npc spawns: " << lvd.npcs.size() << std::endl;
    std::cout << "Number of items: " << lvd.items.size() << std::endl;
}

uint16_t getVersionOfLvdFile(const std::string &filename) {
    std::ifstream load(filename, std::ios::binary);

    char buf[2];

    load.read(buf, 2);
    load.close();
    load.clear();

    return buf[0] * 256 + buf[1];
}

int main(int argc, char *argv[]) {
    cfg::Args args("hi:m:e:");
    
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
    
    LevelD lvld;
    uint16_t version;
    try {
        std::string filename = args.getArgumentValue('i').asString();
        lvld.loadFromFile(filename);
        version = getVersionOfLvdFile(filename);
    } catch (std::exception &e) {
        std::cerr << "ERROR: " << e.what() << std::endl;
        return 1;
    }

    if (args.isSet('e')) {
        std::string expr = args.getArgumentValue('e').asString();
        auto split = Strings::split('=', expr);

        if (split[0] == "id") lvld.metadata.id = split[1];
        else if (split[0] == "name") lvld.metadata.name = split[1];
        else if (split[0] == "author") lvld.metadata.author = split[1];
        else if (split[0] == "description") lvld.metadata.description = split[1];

        if (!args.isSet('m')) {
            std::cerr << "ERROR: -m must be set if -e is used!" << std::endl;
            return 1;
        }
    }

    if (args.isSet('m')) {
        try {
            lvld.saveToFile(args.getArgumentValue('m').asString());
        } catch (std::exception &e) {
            std::cerr << "ERROR: " << e.what() << std::endl;
            return 1;
        }
    }
    else {
        printInfo(lvld, version);
    }

    return 0;
}