#pragma once

#include "../LevelD.hpp"

LevelD::Trigger circleTrigger(
	uint32_t x,
	uint32_t y,
	uint32_t layerId,
	uint16_t radius,
	uint32_t id,
	uint32_t tag,
	uint16_t type,
	uint32_t a1,
	uint32_t a2,
	uint32_t a3,
	uint32_t a4,
	uint32_t a5,
	const std::string& metadata);

LevelD::Trigger rectTrigger(
	uint32_t x,
	uint32_t y,
	uint32_t layerId,
	uint16_t width,
	uint16_t height,
	uint32_t id,
	uint32_t tag,
	uint16_t type,
	uint32_t a1,
	uint32_t a2,
	uint32_t a3,
	uint32_t a4,
	uint32_t a5,
	const std::string& metadata);