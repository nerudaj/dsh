#include "Top.hpp"

void ModuleItems::serialize(BytestreamOut &bout, const LevelD &lvld) const {
    bout << uint32_t(lvld.items.size());

    for (auto &item : lvld.items) {
        bout << item.id << item.x << item.y << item.flags;
    }
}

void ModuleItems::deserialize(BytestreamIn &bin, LevelD &lvld) const {
    uint32_t size;
    bin >> size;

    LevelD::Items items(size);
    for (auto &item : items) {
        bin >> item.id >> item.x >> item.y >> item.flags;
    }

    lvld.items = items;
}