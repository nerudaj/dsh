#include "LevelD.hpp"
#include "Modules/Top.hpp"
#include "Bytestream/Bytestream.hpp"
#include <fstream>
#include <stdexcept>
#include <iostream>

const uint16_t VERSION = 2;

using std::vector;
using std::string;

Module *getModule(uint32_t identity, uint16_t version) {
    if (identity == LVLD_METADATA_CODE)     return new ModuleMetadata;
    else if (identity == LVLD_MESH_CODE)    {
        switch(version) {
        case 1: return new ModuleMesh_v1;
        case 2: return new ModuleMesh_v2;
        }
    }
    else if (identity == LVLD_PLAYERS_CODE) return new ModulePlayers;
    else if (identity == LVLD_ITEMS_CODE)   return new ModuleItems;
    else if (identity == LVLD_NPCS_CODE)    return new ModuleNpcs;
    /*else if (identity == LVLD_EVENTS_CODE)  return new ModuleEvents;*/

    throw std::runtime_error("Unsupported identity code!");
    return NULL;
}

void LevelD::loadFromFile(const string &filename) {
    BytestreamIn bin(filename);
    uint16_t version;
    bin >> version;

    if (version > VERSION) {
        throw std::runtime_error("Unsupported version of LVD!");
    }

    while (!bin.eof()) {
        uint32_t identity;
        bin >> identity;

        auto *module = getModule(identity, version);
        module->deserialize(bin, *this);
        delete module;
    }
}

void LevelD::saveToFile(const string &filename) const {
    BytestreamOut bout(filename);
    bout << VERSION;

    ModuleMetadata metamod;
    bout << LVLD_METADATA_CODE;
    metamod.serialize(bout, *this);

    if (!mesh.empty()) {
        bout << LVLD_MESH_CODE;
        Module* meshmod = getModule(LVLD_MESH_CODE, VERSION);
        meshmod->serialize(bout, *this);
    }

    if (!players.empty()) {
        bout << LVLD_PLAYERS_CODE;
        ModulePlayers plrsmod;
        plrsmod.serialize(bout, *this);
    }

    if (!items.empty()) {
        bout << LVLD_ITEMS_CODE;
        ModuleItems itemmod;
        itemmod.serialize(bout, *this);
    }

    if (!npcs.empty()) {
        bout << LVLD_NPCS_CODE;
        ModuleNpcs npcmod;
        npcmod.serialize(bout, *this);
    }

    /*if (!events.empty()) {
        bout << LVLD_EVENTS_CODE;
        ModuleEvents eventmod;
        eventmd.serialize(bout, *this);
    }*/ 

    bout.close();
}