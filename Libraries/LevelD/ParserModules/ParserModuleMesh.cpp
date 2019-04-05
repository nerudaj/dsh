#include "ParserModule.hpp"
#include <stdexcept>

void ParserModuleMesh::parse(const std::vector<uint8_t> &data, LevelD &leveld) const {
    if (data.size() < 8) {
        throw std::runtime_error("Mesh data chunk is too small!");
    }

    unsigned skip = 0;
    leveld.mesh.width = *((uint32_t*)(data.data() + skip)); skip += 4;
    leveld.mesh.height= *((uint32_t*)(data.data() + skip)); skip += 4;

    unsigned size = leveld.mesh.width * leveld.mesh.height;
    if (8 + size * 2 != data.size()) {
        throw std::runtime_error("Mesh data chunk size does not match width and height specified!");
    }

    leveld.mesh.tiles.resize(size, 0);
    leveld.mesh.collisions.resize(size, 0);

    const uint16_t MSH_BITS = 0x7fff;
    const uint16_t COL_BITS = 0x8000;

    uint16_t *dt = (uint16_t*)(data.data() + 8);
    for (unsigned i = 0, p = 0; i < data.size(); i += 2, p++) {
        leveld.mesh.tiles[p] = dt[i] & MSH_BITS;
        leveld.mesh.collisions[p] = bool(dt[i] & COL_BITS);
    }
}

std::vector<uint8_t> ParserModuleMesh::deparse(const LevelD &leveld) const {
    std::vector<uint8_t> result(16 + leveld.mesh.tiles.size() * 2, 0);
    uint32_t *header = (uint32_t*)result.data();
    uint16_t *data =   (uint16_t*)result.data() + 16;

    header[0] = *((uint32_t*)(std::string("MESH").data()));
    header[1] = result.size() - 8; // size and identification is not part of this field
    header[2] = leveld.mesh.width;
    header[3] = leveld.mesh.height;

    for (unsigned i = 0; i < leveld.mesh.tiles.size(); i++) {
        uint16_t colbit = leveld.mesh.collisions[i] << 15;
        data[i] = leveld.mesh.tiles[i] | colbit;
    }

    return result;
}