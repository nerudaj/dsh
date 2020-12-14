#include <catch.hpp>
#include "../LevelD.hpp"
#include "Assertions.hpp"
#include "Helpers.hpp"

TEST_CASE("Triggers save/load", "[LevelD]") {
	LevelD out;
	LevelD in;

	SECTION("Empty") {
		out.saveToFile("temp.lvd");
		in.loadFromFile("temp.lvd");
	}

	SECTION("/w data") {
		out.triggers = {
			circleTrigger(100, 100, 32, 0, 0, 0, 1, 2, 3, 4, 0, ""),
			rectTrigger(500, 200, 30, 50, 1, 10, 1280, 20, 0, 0, 0, 0, "text")
		};

		out.saveToFile("temp.lvd");
		in.loadFromFile("temp.lvd");
	}

	assertTriggers(in, out);
}
