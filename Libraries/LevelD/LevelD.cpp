#include "LevelD.hpp"
#include "Modules/Top.hpp"
#include "Bytestream/Bytestream.hpp"
#include <fstream>
#include <stdexcept>
#include <iostream>

const uint16_t VERSION = 3;

using std::vector;
using std::string;

Module *getModule(uint32_t identity, uint16_t version) {
    if (identity == LVLD_METADATA_CODE)     return new ModuleMetadata;
    else if (identity == LVLD_MESH_CODE)    {
        switch(version) {
        case 1: return new ModuleMesh_v1;
        case 2: return new ModuleMesh_v2;
		case 3: return new ModuleMesh_v3;
        }
    }
    else if (identity == LVLD_PLAYERS_CODE) return new ModuleNpcsItemsPlayers; // Backward compatibility, replaced by things
    else if (identity == LVLD_ITEMS_CODE)   return new ModuleNpcsItemsPlayers; // Backward compatibility, replaced by things
    else if (identity == LVLD_NPCS_CODE)    return new ModuleNpcsItemsPlayers; // Backward compatibility, replaced by things
	else if (identity == LVLD_THINGS_CODE)  return new ModuleThings;
	else if (identity == LVLD_TRIGGERS_CODE)return new ModuleTriggers;

    throw std::runtime_error("Unsupported identity code: " + std::to_string(identity) + "!");
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

    if (!things.empty()) {
        bout << LVLD_THINGS_CODE;
        ModuleThings thngmod;
        thngmod.serialize(bout, *this);
    }

    if (!triggers.empty()) {
        bout << LVLD_TRIGGERS_CODE;
        ModuleTriggers trigmod;
        trigmod.serialize(bout, *this);
    }

    bout.close();
}