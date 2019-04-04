#pragma once

#include <string>
#include <cstdint>
#include <vector>

/**
 *  \brief Class representing LevelD file in memory
 */
class LevelD {
public:
    struct {
        uint32_t              width;
        uint32_t              height;
        std::vector<uint16_t> tiles;
        std::vector<bool>     collisions;
    } mesh;

    void loadFromFile(const std::string &filename);

    void saveToFile(const std::string &filename) const;
};