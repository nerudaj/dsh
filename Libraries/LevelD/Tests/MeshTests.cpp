#include <catch.hpp>
#include "../LevelD.hpp"

TEST_CASE("Mesh save/load", "[LevelD]") {
	LevelD out;
	LevelD in;

	SECTION("Empty") {
		out.saveToFile("temp.lvd");
		in.loadFromFile("temp.lvd");
	}

	SECTION("/w data") {
		out.mesh = {2, 2, {1, 2, 3, 4}, {1, 0, 0, 1}};
		out.saveToFile("temp.lvd");
		in.loadFromFile("temp.lvd");
	}

	REQUIRE(out.mesh.width == in.mesh.width);
	REQUIRE(out.mesh.height == in.mesh.height);
	REQUIRE(out.mesh.width *  out.mesh.height == out.mesh.tiles.size());
	REQUIRE(out.mesh.width *  out.mesh.height == out.mesh.blocks.size());

	for (unsigned i = 0; i < out.mesh.tiles.size(); i++) {
		REQUIRE(out.mesh.tiles[i] == in.mesh.tiles[i]);
		REQUIRE(out.mesh.blocks[i] == in.mesh.blocks[i]);
	}
}