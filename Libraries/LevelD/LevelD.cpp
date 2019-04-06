#include "LevelD.hpp"
#include "ParserModules/Top.hpp"
#include <fstream>
#include <stdexcept>
#include <iostream>

const uint16_t VERSION = 0;

using std::vector;
using std::string;

void LevelD::loadFromFile(const string &filename) {
    // Open filehandle
    std::ifstream load(filename, std::ios::binary);

    load.seekg(0, load.end);
    unsigned fsize = load.tellg();
    load.seekg(0, load.beg);

    if (fsize < 10) {
        throw std::runtime_error("File is corrupt!");
    }

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
    unsigned loaded = 6; // loaded 6 bytes so far
    while (loaded < fsize) {
        // Create parser module
        load.read((char*)identity.data(), identity.size());
        if (load.eof()) break; // Loop ends OK

        std::cerr << identity << std::endl;

        ParserModule *module = ParserModule::getModule(identity);

        if (module == NULL) {
            throw std::runtime_error("Unknown module identification '" + identity + "'");
        }

        // Load chunk size, alloc memory for chunk, load chunk and parse it by module
        uint32_t chunkSize = 0;
        load.read((char*)(&chunkSize), sizeof(chunkSize));
        vector<uint8_t> data(chunkSize, 0);
        load.read((char*)data.data(), chunkSize);

        // Use module to parse chunk of data and save result to this
        module->parse(data, *this);
        delete module;

        loaded += 8 + chunkSize; // identity, chunkSize, chunk

        identity = "xxxx";
    }

    load.clear();
    load.close();
}

void LevelD::saveToFile(const string &filename) const {
    std::ofstream save(filename, std::ios::binary);

    // Write identification and version
    save.write("LVLD", 4);
    save.write((char*)(&VERSION), sizeof(VERSION));

    // Save data of each supported module
    if (mesh.width * mesh.height != 0) {
        auto *module = ParserModule::getModule("MESH");
        auto mesh = module->deparse(*this);
        save.write((char*)(mesh.data()), mesh.size());
        delete module;
    }

    if (!players.empty()) {
        auto *module = ParserModule::getModule("PLAS");
        auto plas = module->deparse(*this);
        save.write((char*)(plas.data()), plas.size());
        delete module;
    }

    // Always export metadata
    auto *module = ParserModule::getModule("META");
    auto meta = module->deparse(*this);
    save.write((char*)(meta.data()), meta.size());
    delete module;

    save.close();
    save.clear();
}