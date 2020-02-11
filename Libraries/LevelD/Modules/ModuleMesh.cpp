#include "Top.hpp"

void ModuleMesh_v1::serialize(BytestreamOut &bout, const LevelD &lvld) const {
    bout << lvld.mesh.width;

    std::vector<uint16_t> dataout(lvld.mesh.width * lvld.mesh.height);

    for (unsigned i = 0; i < dataout.size(); i++) {
        dataout[i] = (lvld.mesh.blocks[i] << 15) | lvld.mesh.tiles[i];
    }

    bout << dataout;
}

void ModuleMesh_v1::deserialize(BytestreamIn &bin, LevelD &lvld) const {
    uint32_t width;
    std::vector<uint16_t> data;

    bin >> width >> data;

    lvld.mesh.width = width;
    lvld.mesh.height = data.size() / width;
    lvld.mesh.tiles.resize(data.size(), 0);
    lvld.mesh.blocks.resize(data.size(), 0);

    const uint16_t TILES_BITS = 0x7fff;
    const uint16_t BLOCK_BITS = 0x8000;

    for (unsigned i = 0; i < data.size(); i++) {
        lvld.mesh.tiles[i] = data[i] & TILES_BITS;
        lvld.mesh.blocks[i]= bool(data[i] & BLOCK_BITS);
    }
}

void ModuleMesh_v2::serialize(BytestreamOut &bout, const LevelD &lvld) const {
    bout << lvld.mesh.tileWidth << lvld.mesh.tileHeight << lvld.mesh.width;

    std::vector<uint16_t> dataout(lvld.mesh.width * lvld.mesh.height);

    for (unsigned i = 0; i < dataout.size(); i++) {
        dataout[i] = (lvld.mesh.blocks[i] << 15) | lvld.mesh.tiles[i];
    }

    bout << dataout;
}

void ModuleMesh_v2::deserialize(BytestreamIn &bin, LevelD &lvld) const {
    uint16_t tileW, tileH;
    uint32_t width;
    std::vector<uint16_t> data;

    bin >> tileW >> tileH >> width >> data;

    lvld.mesh.tileWidth = tileW;
    lvld.mesh.tileHeight = tileH;
    lvld.mesh.width = width;
    lvld.mesh.height = data.size() / width;
    lvld.mesh.tiles.resize(data.size(), 0);
    lvld.mesh.blocks.resize(data.size(), 0);

    const uint16_t TILES_BITS = 0x7fff;
    const uint16_t BLOCK_BITS = 0x8000;

    for (unsigned i = 0; i < data.size(); i++) {
        lvld.mesh.tiles[i] = data[i] & TILES_BITS;
        lvld.mesh.blocks[i]= bool(data[i] & BLOCK_BITS);
    }
}