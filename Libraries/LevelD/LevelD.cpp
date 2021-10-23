#include "LevelD.hpp"
#include "Modules/Top.hpp"
#include "Bytestream/Bytestream.hpp"
#include <fstream>
#include <stdexcept>
#include <iostream>
#include <memory>

const uint16_t VERSION = 3;

using std::vector;
using std::string;

std::unique_ptr<Module> getModule(uint32_t identity, uint16_t version) {
	switch (identity) {
	case LVLD_METADATA_CODE:
		return std::make_unique<ModuleMetadata>();
	case LVLD_MESH_CODE: {
		switch (version) {
		case 1: return std::make_unique<ModuleMesh_v1>();
		case 2: return std::make_unique<ModuleMesh_v2>();
		case 3: return std::make_unique<ModuleMesh_v3>();
		}
	}
	case LVLD_PLAYERS_CODE:
	case LVLD_ITEMS_CODE:
	case LVLD_NPCS_CODE:
		return std::make_unique<ModuleNpcsItemsPlayers>();
	case LVLD_THINGS_CODE:
		return std::make_unique<ModuleThings>();
	case LVLD_TRIGGERS_CODE:
		return std::make_unique<ModuleTriggers>();
	case LVLD_PATHS_CODE:
		return std::make_unique<ModulePaths>();
	default:
		break;
	}
	
	throw std::runtime_error("Unsupported identity code: " + std::to_string(identity) + "!");
	return nullptr;
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

        auto module = getModule(identity, version);
        module->deserialize(bin, *this);
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
        auto meshmod = getModule(LVLD_MESH_CODE, VERSION);
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
	
	if (!paths.empty()) {
        bout << LVLD_PATHS_CODE;
        ModulePaths pathmod;
        pathmod.serialize(bout, *this);
    }

    bout.close();
}