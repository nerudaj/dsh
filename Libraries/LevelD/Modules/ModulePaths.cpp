#include "Top.hpp"
#include <stdexcept>

void ModulePaths::serialize(BytestreamOut& bout, const LevelD& lvld) const
{
	throw std::runtime_error("DEPRECATED: Trying to serialize using outdated ModulePaths");
}

void ModulePaths::deserialize(BytestreamIn& bin, LevelD& lvld) const
{
	auto getArraySize = [&]() -> uint32_t
	{
		uint32_t size;
		bin >> size;
		return size;
	};

	auto getBoolValue = [&]() -> bool
	{
		uint8_t r;
		bin >> r;
		return static_cast<bool>(r);
	};

	uint32_t pathCount = getArraySize();

	LevelD::Paths paths(pathCount);
	for (auto& path : paths)
	{
		path.looping = getBoolValue();
		bin >> path.tag;
		path.layerId = 0;
		const uint32_t pointCount = getArraySize();

		path.points.resize(pointCount);
		for (auto& point : path.points)
		{
			bin >> point.x;
			bin >> point.y;
			bin >> point.value;
		}
	}

	lvld.paths = paths;
}

void ModulePaths_v4::serialize(BytestreamOut& bout, const LevelD& lvld) const
{
	bout << static_cast<uint32_t>(lvld.paths.size());

	for (auto&& path : lvld.paths)
	{
		bout << static_cast<uint8_t>(path.looping);
		bout << path.tag;
		bout << path.layerId;
		bout << static_cast<uint32_t>(path.points.size());

		for (auto&& point : path.points)
		{
			bout << point.x << point.y << point.value;
		}
	}
}

void ModulePaths_v4::deserialize(BytestreamIn& bin, LevelD& lvld) const
{
	auto getArraySize = [&]() -> uint32_t
	{
		uint32_t size;
		bin >> size;
		return size;
	};

	auto getBoolValue = [&]() -> bool
	{
		uint8_t r;
		bin >> r;
		return static_cast<bool>(r);
	};

	uint32_t pathCount = getArraySize();

	LevelD::Paths paths(pathCount);
	for (auto& path : paths)
	{
		path.looping = getBoolValue();
		bin >> path.tag;
		bin >> path.layerId;
		const uint32_t pointCount = getArraySize();

		path.points.resize(pointCount);
		for (auto& point : path.points)
		{
			bin >> point.x;
			bin >> point.y;
			bin >> point.value;
		}
	}

	lvld.paths = paths;
}
