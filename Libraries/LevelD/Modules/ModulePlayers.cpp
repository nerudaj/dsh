#include "Top.hpp"

void ModulePlayers::serialize(BytestreamOut &bout, const LevelD &lvld) const {
    bout << uint32_t(lvld.players.size());

    for (auto &player : lvld.players) {
        bout << player.id << player.x << player.y << player.flags;
    }
}

void ModulePlayers::deserialize(BytestreamIn &bin, LevelD &lvld) const {
    uint32_t size;
    bin >> size;

    LevelD::Players players(size);
    for (auto &player : players) {
        bin >> player.id >> player.x >> player.y >> player.flags;
    }

    lvld.players = players;
}