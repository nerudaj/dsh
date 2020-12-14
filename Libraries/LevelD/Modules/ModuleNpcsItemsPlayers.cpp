#include "Top.hpp"
#include <stdexcept>

void ModuleNpcsItemsPlayers::serialize(BytestreamOut &bout, const LevelD &lvld) const {
    std::runtime_error("DEPRECATED: Trying to serialize using ModuleNpcsItemsPlayers");
}

void ModuleNpcsItemsPlayers::deserialize(BytestreamIn &bin, LevelD &lvld) const {
    uint32_t size;
    bin >> size;

	LevelD::Things things(size);
    for (auto &thing : things) {
		bin >> thing.id;
		thing.tag = 0;
		bin >> thing.x >> thing.y >> thing.flags;
		thing.metadata = "";
    }

    lvld.things.insert(lvld.things.end(), things.begin(), things.end());
}