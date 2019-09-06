#include "Top.hpp"

void ModuleNpcs::serialize(BytestreamOut &bout, const LevelD &lvld) const {
    bout << uint32_t(lvld.npcs.size());

    for (auto &npc : lvld.npcs) {
        bout << npc.id << npc.x << npc.y << npc.flags;
    }
}

void ModuleNpcs::deserialize(BytestreamIn &bin, LevelD &lvld) const {
    uint32_t size;
    bin >> size;

    LevelD::Npcs npcs(size);
    for (auto &npc : npcs) {
        bin >> npc.id >> npc.x >> npc.y >> npc.flags;
    }

    lvld.npcs = npcs;
}