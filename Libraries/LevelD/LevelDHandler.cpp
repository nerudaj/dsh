#include "LevelDHandler.hpp"
#include "ParserModules/ParserModule.hpp"
#include <fstream>
#include <stdexcept>

const uint16_t VERSION = 0;

using std::vector;
using std::string;

LevelD loadFile(const string &filename) {
    LevelD result;

    // Open filehandle
    std::ifstream load(filename, std::ios::binary);

    // Load identity chunk
    string identity("xxxx");
    load.read((char*)identity.data(), identity.size());

    if (identity != "LVLD") {
        throw std::runtime_error("File is not of LevelD format!");
    }

    // Load version chunk
    uint16_t version;
    load.read((char*)(&version), sizeof(version));

    if (version > VERSION) {
        throw std::runtime_error("This parser can only load files up to version " + std::to_string(VERSION) + " but this file has version of " + std::to_string(version) );
    }

    // Load submodules
    uint32_t chunkSize;
    while (load.good()) {
        // Create parser module
        load.read((char*)identity.data(), identity.size());
        ParserModule *module = ParserModule::getModule(identity);

        // Load chunk size, alloc memory for chunk, load chunk and parse it by module
        load.read((char*)(&chunkSize), sizeof(chunkSize));
        vector<uint8_t> data(chunkSize, 0);
        load.read((char*)data.data(), chunkSize);
        module->parse(data, result);
        delete module;
    }

    load.clear();
    load.close();

    return result;
}

void saveFile(const string &filename, const LevelD &level) {
    std::ofstream save(filename, std::ios::binary);

    // Write identification and version
    save.write("LVLD", 8);
    save.write((char*)(&VERSION), sizeof(VERSION));

    // Save data of each supported module
    auto *module = ParserModule::getModule("MESH");
    auto mesh = module->deparse(level);
    save.write((char*)(mesh.data()), mesh.size());
    delete module;

    save.close();
    save.clear();
}