#include "Top.hpp"
#include <stdexcept>

/* Version 1 */
void ModuleMesh_v1::serialize(BytestreamOut &bout, const LevelD &lvld) const {
    throw std::runtime_error("Trying to serialize mesh using outdated ModuleMesh_v1");
}

void ModuleMesh_v1::deserialize(BytestreamIn &bin, LevelD &lvld) const {
    uint32_t width;
    std::vector<uint16_t> data;

    bin >> width >> data;

	lvld.mesh.tileWidth = 0;
	lvld.mesh.tileHeight = 0;
    lvld.mesh.layerWidth = width;
    lvld.mesh.layerHeight = data.size() / width;

	lvld.mesh.layers.resize(1);

	auto &layer = lvld.mesh.layers[0];
    layer.tiles.resize(data.size(), 0);
    layer.blocks.resize(data.size(), 0);

    const uint16_t TILES_BITS = 0x7fff;
    const uint16_t BLOCK_BITS = 0x8000;

    for (unsigned i = 0; i < data.size(); i++) {
        layer.tiles[i] = data[i] & TILES_BITS;
        layer.blocks[i]= bool(data[i] & BLOCK_BITS);
    }
}

/* Version 2 - Added tile data */
void ModuleMesh_v2::serialize(BytestreamOut &bout, const LevelD &lvld) const {
    throw std::runtime_error("Trying to serialize mesh using outdated ModuleMesh_v2");
}

void ModuleMesh_v2::deserialize(BytestreamIn &bin, LevelD &lvld) const {
    uint16_t tileW, tileH;
    uint32_t width;
    std::vector<uint16_t> data;

    bin >> tileW >> tileH >> width >> data;

    lvld.mesh.tileWidth = tileW;
    lvld.mesh.tileHeight = tileH;
    lvld.mesh.layerWidth = width;
    lvld.mesh.layerHeight = data.size() / width;

	lvld.mesh.layers.resize(1);

	auto &layer = lvld.mesh.layers[0];
    layer.tiles.resize(data.size(), 0);
    layer.blocks.resize(data.size(), 0);

    const uint16_t TILES_BITS = 0x7fff;
    const uint16_t BLOCK_BITS = 0x8000;

    for (unsigned i = 0; i < data.size(); i++) {
        layer.tiles[i] = data[i] & TILES_BITS;
        layer.blocks[i]= bool(data[i] & BLOCK_BITS);
    }
}

/* Version 3 - First layered */
void ModuleMesh_v3::serialize(BytestreamOut &bout, const LevelD &lvld) const {
	bout << lvld.mesh.tileWidth << lvld.mesh.tileHeight;
	bout << lvld.mesh.layerWidth << lvld.mesh.layerHeight;
	bout << lvld.mesh.layers.size();

	for (auto &layer : lvld.mesh.layers) {
		std::vector<uint16_t> dataout(lvld.mesh.layerWidth * lvld.mesh.layerHeight);
		for (unsigned i = 0; i < dataout.size(); i++) {
			dataout[i] = (layer.blocks[i] << 15) | layer.tiles[i];
		}

		bout << dataout;
	}
}

void ModuleMesh_v3::deserialize(BytestreamIn &bin, LevelD &lvld) const {
	uint16_t tileW, tileH;
	uint32_t width, height, layerC;

	const uint16_t TILES_BITS = 0x7fff;
    const uint16_t BLOCK_BITS = 0x8000;

	bin >> tileW >> tileH >> width >> height >> layerC;

	lvld.mesh.tileWidth = tileW;
	lvld.mesh.tileHeight = tileH;
	lvld.mesh.layerWidth = width;
	lvld.mesh.layerHeight = height;

	std::vector<LevelD::TileLayer> layers(layerC);
	for (auto &layer : layers) {
		std::vector<uint16_t> data;

		bin >> data;
		if (data.size() != width * height) {
			throw std::runtime_error("Mesh layer size mismatches specified layerWidth and layerHeight");
		}

		layer.tiles.resize(data.size());
		layer.blocks.resize(data.size());

		for (unsigned i = 0; i < data.size(); i++) {
			layer.tiles[i] = data[i] & TILES_BITS;
			layer.blocks[i]= bool(data[i] & BLOCK_BITS);
		}
	}

	lvld.mesh.layers = layers;
}