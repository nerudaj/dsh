#include "LevelD.hpp"
#include "Modules/Top.hpp"
#include "Bytestream/Bytestream.hpp"
#include <fstream>
#include <stdexcept>
#include <iostream>

const uint16_t VERSION = 0;

using std::vector;
using std::string;

Module *getModule(uint32_t identity) {
    if (identity == LVLD_METADATA_CODE)     return new ModuleMetadata;
    else if (identity == LVLD_MESH_CODE)    return new ModuleMesh;
    else if (identity == LVLD_PLAYERS_CODE) return new ModulePlayers;
    else if (identity == LVLD_ITEMS_CODE)   return new ModuleItems;

    throw std::runtime_error("Unsupported identity code!");
    return NULL;
}

void LevelD::loadFromFile(const string &filename) {
    BytestreamIn bin(filename);
    uint16_t version;
    bin >> version;

    if (version != VERSION) {
        throw std::runtime_error("Unsupported version of LVD!");
    }

    while (!bin.eof()) {
        uint32_t identity;
        bin >> identity;

        auto *module = getModule(identity);
        module->deserialize(bin, *this);
        delete module;
    }
}

void LevelD::saveToFile(const string &filename) const {
    BytestreamOut bout(filename);
    bout << VERSION;

    // Always save metadata
    ModuleMetadata metamod;
    metamod.serialize(bout, *this);

    if (!mesh.empty()) {
        ModuleMesh meshmod;
        meshmod.serialize(bout, *this);
    }

    // Sometimes save players
    if (!players.empty()) {
        ModulePlayers plrsmod;
        plrsmod.serialize(bout, *this);
    }

    // Sometimes save items
    if (!items.empty()) {
        ModuleItems itemmod;
        itemmod.serialize(bout, *this);
    }

    bout.close();
}