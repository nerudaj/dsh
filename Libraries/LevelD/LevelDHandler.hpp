#pragma once

#include <string>
#include <cstdint>
#include <vector>

struct LevelD {
    struct {
        uint32_t              width;
        uint32_t              height;
        std::vector<uint16_t> tiles;
        std::vector<bool>     collisions;
    } mesh;
};

class LevelDHandler {
public:
    static LevelD loadFile(const std::string &filename);

    static void saveFile(const std::string &filename, const LevelD &level);
};