#pragma once

#include "../LevelD.hpp"
#include "../Bytestream/Bytestream.hpp"

const uint32_t LVLD_METADATA_CODE = 0x4154454D; // 'META'
const uint32_t LVLD_MESH_CODE     = 0x4853454D; // 'MESH'
const uint32_t LVLD_PLAYERS_CODE  = 0x53524C50; // 'PLRS'
const uint32_t LVLD_ITEMS_CODE    = 0x4D455449; // 'ITEM'
const uint32_t LVLD_NPCS_CODE     = 0x5343504E; // 'NPCS'
const uint32_t LVLD_EVENTS_CODE   = 0x544E5645; // 'EVNT'

class Module {
public:
    virtual void serialize(BytestreamOut &bout, const LevelD &lvld) const =0;
    virtual void deserialize(BytestreamIn &bin, LevelD &lvld) const =0;
};

class ModuleMetadata : public Module {
public:
    virtual void serialize(BytestreamOut &bout, const LevelD &lvld) const final override;
    virtual void deserialize(BytestreamIn &bin, LevelD &lvld) const final override;
};

class ModuleMesh : public Module {
public:
    virtual void serialize(BytestreamOut &bout, const LevelD &lvld) const final override;
    virtual void deserialize(BytestreamIn &bin, LevelD &lvld) const final override;
};

class ModulePlayers : public Module {
public:
    virtual void serialize(BytestreamOut &bout, const LevelD &lvld) const final override;
    virtual void deserialize(BytestreamIn &bin, LevelD &lvld) const final override;
};

class ModuleItems : public Module {
public:
    virtual void serialize(BytestreamOut &bout, const LevelD &lvld) const final override;
    virtual void deserialize(BytestreamIn &bin, LevelD &lvld) const final override;
};

class ModuleNpcs : public Module {
public:
    virtual void serialize(BytestreamOut &bout, const LevelD &lvld) const final override;
    virtual void deserialize(BytestreamIn &bin, LevelD &lvld) const final override;
};

class ModuleEvents : public Module {
public:
    virtual void serialize(BytestreamOut &bout, const LevelD &lvld) const final override;
    virtual void deserialize(BytestreamIn &bin, LevelD &lvld) const final override;
};