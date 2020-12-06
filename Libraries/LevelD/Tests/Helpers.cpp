#include "Helpers.hpp"

LevelD::Trigger circleTrigger(uint32_t x, uint32_t y, uint16_t radius, uint32_t id, uint32_t tag, uint16_t type, uint32_t a1, uint32_t a2, uint32_t a3, uint32_t a4, uint32_t a5, const std::string &metadata) {
	LevelD::Trigger t;
	t.x = x;
	t.y = y;
	t.areaType = LevelD::Trigger::AreaType::Circle;
	t.radius = radius;
	t.width = 0;
	t.height = 0;
	t.id = id;
	t.tag = tag;
	t.type = type;
	t.a1 = a1;
	t.a2 = a2;
	t.a3 = a3;
	t.a4 = a4;
	t.a5 = a5;
	t.metadata = metadata;
	return t;
}

LevelD::Trigger rectTrigger(uint32_t x, uint32_t y, uint16_t width, uint16_t height, uint32_t id, uint32_t tag, uint16_t type, uint32_t a1, uint32_t a2, uint32_t a3, uint32_t a4, uint32_t a5, const std::string &metadata) {
	LevelD::Trigger t;
	t.x = x;
	t.y = y;
	t.areaType = LevelD::Trigger::AreaType::Rectangle;
	t.radius = 0;
	t.width = width;
	t.height = height;
	t.id = id;
	t.tag = tag;
	t.type = type;
	t.a1 = a1;
	t.a2 = a2;
	t.a3 = a3;
	t.a4 = a4;
	t.a5 = a5;
	t.metadata = metadata;
	return t;
}