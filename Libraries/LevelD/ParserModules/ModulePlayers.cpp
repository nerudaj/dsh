#include "Top.hpp"
#include <stdexcept>
#include <iostream>

void ParserModulePlayers::parse(const std::vector<uint8_t> &data, LevelD &leveld) const {
    if (data.size() % sizeof(LevelD::Player) != 0) {
        throw std::runtime_error("Players data chunk has bad size!");
    }

    leveld.players.resize(data.size() / sizeof(LevelD::Player));

    unsigned i = 0;
    while (i < leveld.players.size()) {
        LevelD::Player *player = (LevelD::Player*)data.data() + i;
        leveld.players[i] = *player;
        i++;
    }
}

std::vector<uint8_t> ParserModulePlayers::deparse(const LevelD &leveld) const {
    std::vector<uint8_t> result(4 + 4 + sizeof(LevelD::Player) * leveld.players.size());

    uint32_t *header = (uint32_t*)result.data();
    LevelD::Player *data = (LevelD::Player*)(result.data() + 2 * sizeof(uint32_t));

    header[0] = *((uint32_t*)(std::string("PLAS").data()));
    header[1] = result.size() - 8; // Identity and size is not part of this field

    for (unsigned i = 0; i < leveld.players.size(); i++) {
        data[i] = leveld.players[i];
    }

    return result;
}