#include <catch.hpp>
#include "../LevelD.hpp"
#include "Assertions.hpp"

TEST_CASE("Mesh save/load", "[LevelD]") {
	LevelD out;
	LevelD in;

	SECTION("Empty") {
		REQUIRE(out.mesh.empty());
	}

	SECTION("Defined mesh without layers") {
		out.mesh = {16, 24, 2, 2, {}};
		REQUIRE(!out.mesh.empty());
	}

	SECTION("Defined mesh with layers") {
		out.mesh = {16, 24, 2, 2, {}};
		out.mesh.layers.push_back({
			{ 1, 2, 3, 4 }, { 1, 1, 0, 0 }
		});
	}

	out.saveToFile("temp.lvd");
	in.loadFromFile("temp.lvd");

	assertMesh(in, out);
}
