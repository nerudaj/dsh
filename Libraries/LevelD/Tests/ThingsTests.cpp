#include <catch.hpp>
#include "../LevelD.hpp"
#include "Assertions.hpp"

TEST_CASE("Things save/load", "[LevelD]") {
	LevelD out;
	LevelD in;

	SECTION("Empty") {
		out.saveToFile("temp.lvd");
		in.loadFromFile("temp.lvd");
	}

	SECTION("/w data") {
		out.things = {
			{0, 0, 10, 20, 4, ""},
			{1, 1, 2, 15, 0, "silent"},
			{2, 0, 244, 300, 10, ""}
		};
		out.saveToFile("temp.lvd");
		in.loadFromFile("temp.lvd");
	}

	assertThings(in, out);
}
