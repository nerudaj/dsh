#include "Top.hpp"

void ModuleThings::serialize(BytestreamOut &bout, const LevelD &lvld) const {
    bout << uint32_t(lvld.things.size());

    for (auto &thing : lvld.things) {
        bout << thing.id << thing.tag;
		bout << thing.x << thing.y;
		bout << thing.flags << thing.metadata;
    }
}

void ModuleThings::deserialize(BytestreamIn &bin, LevelD &lvld) const {
    uint32_t size;
    bin >> size;

    LevelD::Things things(size);
    for (auto &thing : things) {
        bin >> thing.id >> thing.tag;
		bin >> thing.x >> thing.y;
		bin >> thing.flags >> thing.metadata;
    }

    lvld.things = things;
}