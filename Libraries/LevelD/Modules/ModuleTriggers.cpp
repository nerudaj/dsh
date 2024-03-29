#include "Top.hpp"
#include <stdexcept>

void ModuleTriggers::serialize(BytestreamOut& bout, const LevelD& lvld) const
{
	throw std::runtime_error("DEPRECATED: Trying to serialize using outdated ModuleTriggers");
}

void ModuleTriggers::deserialize(BytestreamIn& bin, LevelD& lvld) const
{
	using AreaType = LevelD::Trigger::AreaType;

	uint32_t trigC;
	uint8_t type;

	bin >> trigC;

	LevelD::Triggers triggers(trigC);
	for (auto& trig : triggers)
	{
		bin >> trig.x >> trig.y >> type;
		trig.layerId = 0;
		trig.areaType = static_cast<AreaType>(type);

		if (trig.areaType == AreaType::Rectangle)
		{
			trig.radius = 0;
			bin >> trig.width >> trig.height;
		}
		else if (trig.areaType == AreaType::Circle)
		{
			bin >> trig.radius;
			trig.width = 0;
			trig.height = 0;
		}

		bin >> trig.id >> trig.tag >> trig.type;
		bin >> trig.a1;
		bin >> trig.a2;
		bin >> trig.a3;
		bin >> trig.a4;
		bin >> trig.a5;
		bin >> trig.metadata;
	}

	lvld.triggers = triggers;
}

void ModuleTriggers_v4::serialize(BytestreamOut& bout, const LevelD& lvld) const
{
	using AreaType = LevelD::Trigger::AreaType;

	bout << uint32_t(lvld.triggers.size());

	for (auto& trigger : lvld.triggers)
	{
		bout << trigger.x << trigger.y << trigger.layerId;
		bout << uint8_t(trigger.areaType);

		if (trigger.areaType == AreaType::Rectangle)
		{
			bout << trigger.width << trigger.height;
		}
		else if (trigger.areaType == AreaType::Circle)
		{
			bout << trigger.radius;
		}

		bout << trigger.id << trigger.tag << trigger.type;
		bout << trigger.a1;
		bout << trigger.a2;
		bout << trigger.a3;
		bout << trigger.a4;
		bout << trigger.a5;
		bout << trigger.metadata;
	}
}

void ModuleTriggers_v4::deserialize(BytestreamIn& bin, LevelD& lvld) const
{
	using AreaType = LevelD::Trigger::AreaType;

	uint32_t trigC;
	uint8_t type;

	bin >> trigC;

	LevelD::Triggers triggers(trigC);
	for (auto& trig : triggers)
	{
		bin >> trig.x >> trig.y >> trig.layerId >> type;
		trig.areaType = static_cast<AreaType>(type);

		if (trig.areaType == AreaType::Rectangle)
		{
			trig.radius = 0;
			bin >> trig.width >> trig.height;
		}
		else if (trig.areaType == AreaType::Circle)
		{
			bin >> trig.radius;
			trig.width = 0;
			trig.height = 0;
		}

		bin >> trig.id >> trig.tag >> trig.type;
		bin >> trig.a1;
		bin >> trig.a2;
		bin >> trig.a3;
		bin >> trig.a4;
		bin >> trig.a5;
		bin >> trig.metadata;
	}

	lvld.triggers = triggers;
}
