#include "Top.hpp"
#include <stdexcept>

void ModuleThings::serialize(BytestreamOut& bout, const LevelD& lvld) const
{
	std::runtime_error("DEPRECATED: Trying to serialize using outdated ModuleThings");
}

void ModuleThings::deserialize(BytestreamIn& bin, LevelD& lvld) const
{
	uint32_t size;
	bin >> size;

	LevelD::Things things(size);
	for (auto& thing : things)
	{
		bin >> thing.id >> thing.tag;
		bin >> thing.x >> thing.y;
		bin >> thing.flags >> thing.metadata;
		thing.layerId = 0;
	}

	lvld.things = things;
}

void ModuleThings_v4::serialize(BytestreamOut& bout, const LevelD& lvld) const
{
	bout << uint32_t(lvld.things.size());

	for (auto& thing : lvld.things)
	{
		bout << thing.id << thing.tag;
		bout << thing.x << thing.y << thing.layerId;
		bout << thing.flags << thing.metadata;
	}
}

void ModuleThings_v4::deserialize(BytestreamIn& bin, LevelD& lvld) const
{
	uint32_t size;
	bin >> size;

	LevelD::Things things(size);
	for (auto& thing : things)
	{
		bin >> thing.id >> thing.tag;
		bin >> thing.x >> thing.y >> thing.layerId;
		bin >> thing.flags >> thing.metadata;
	}

	lvld.things = things;
}
