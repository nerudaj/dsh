#pragma once

#include "../LevelD.hpp"
#include "../Bytestream/Bytestream.hpp"

const uint32_t LVLD_METADATA_CODE = 0x4D455441; // 'META'
const uint32_t LVLD_MESH_CODE     = 0x4D455348; // 'MESH'
const uint32_t LVLD_THINGS_CODE   = 0x54484E47; // 'THNG'
const uint32_t LVLD_PLAYERS_CODE  = 0x504C5253; // 'PLRS'
const uint32_t LVLD_ITEMS_CODE    = 0x4954454D; // 'ITEM'
const uint32_t LVLD_NPCS_CODE     = 0x4E504353; // 'NPCS'
const uint32_t LVLD_TRIGGERS_CODE = 0x54524947; // 'TRIG'

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

class ModuleMesh_v1 : public Module {
public:
    virtual void serialize(BytestreamOut &bout, const LevelD &lvld) const final override;
    virtual void deserialize(BytestreamIn &bin, LevelD &lvld) const final override;
};

class ModuleMesh_v2 : public Module {
public:
    virtual void serialize(BytestreamOut &bout, const LevelD &lvld) const final override;
    virtual void deserialize(BytestreamIn &bin, LevelD &lvld) const final override;
};

class ModuleMesh_v3 : public Module {
public:
    virtual void serialize(BytestreamOut &bout, const LevelD &lvld) const final override;
    virtual void deserialize(BytestreamIn &bin, LevelD &lvld) const final override;
};

class ModuleNpcsItemsPlayers : public Module {
public:
    virtual void serialize(BytestreamOut &bout, const LevelD &lvld) const final override;
    virtual void deserialize(BytestreamIn &bin, LevelD &lvld) const final override;
};

class ModuleThings : public Module {
public:
    virtual void serialize(BytestreamOut &bout, const LevelD &lvld) const final override;
    virtual void deserialize(BytestreamIn &bin, LevelD &lvld) const final override;
};

class ModuleTriggers : public Module {
public:
    virtual void serialize(BytestreamOut &bout, const LevelD &lvld) const final override;
    virtual void deserialize(BytestreamIn &bin, LevelD &lvld) const final override;
};