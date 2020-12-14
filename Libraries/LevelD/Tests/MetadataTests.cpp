#include <catch.hpp>
#include "../LevelD.hpp"
#include "Assertions.hpp"

TEST_CASE("Metadata save/load", "[LevelD]") {
	LevelD out;
	LevelD in;

	SECTION("Empty") {
		out.saveToFile("temp.lvd");
		in.loadFromFile("temp.lvd");
	}

	SECTION("/w data") {
		out.metadata = { "map01", "Hangar", "doomista", "First level", 10 };
		out.saveToFile("temp.lvd");
		in.loadFromFile("temp.lvd");
	}

	assertMetadata(in, out);
}