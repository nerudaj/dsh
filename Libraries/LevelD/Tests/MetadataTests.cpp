#include <catch.hpp>
#include "../LevelD.hpp"

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

	REQUIRE(in.metadata.timestamp == out.metadata.timestamp);
	REQUIRE(in.metadata.id == out.metadata.id);
	REQUIRE(in.metadata.name == out.metadata.name);
	REQUIRE(in.metadata.author == out.metadata.author);
	REQUIRE(in.metadata.description == out.metadata.description);
}