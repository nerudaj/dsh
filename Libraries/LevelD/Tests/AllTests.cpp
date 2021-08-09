#include <catch.hpp>
#include "../LevelD.hpp"
#include "Assertions.hpp"
#include "Helpers.hpp"

TEST_CASE("Everything save/load", "[LevelD]") {
	LevelD out;
	LevelD in;

	SECTION("Empty") {
		out.saveToFile("temp.lvd");
		in.loadFromFile("temp.lvd");
	}

	SECTION("Data") {
		out.metadata = { "map01", "Hangar", "doomista", "First level", 10 };
		out.mesh = {16, 24, 2, 2, {}};
		out.mesh.layers.push_back({
			{ 1, 2, 3, 4 }, { 1, 1, 0, 0 }
		});
		out.things = {
			{0, 0, 10, 20, 4, ""},
			{1, 1, 2, 15, 0, "silent"},
			{2, 0, 244, 300, 10, ""}
		};
		out.triggers = {
			circleTrigger(100, 100, 32, 0, 0, 0, 1, 2, 3, 4, 0, ""),
			rectTrigger(500, 200, 30, 50, 1, 10, 1280, 20, 0, 0, 0, 0, "text")
		};
		out.saveToFile("temp.lvd");
		in.loadFromFile("temp.lvd");
	}

	assertMetadata(in, out);
	assertMesh(in, out);
	assertThings(in, out);
	assertTriggers(in, out);
}

// Bug #1 - Create a LVD mesh 40x40 with 1 layer and add any number of things - it will incorrectly export the things mesh
// NOTE: Cause of the bug was that chunk size used for resizing internal output buffer was smaller than the size of the
// mesh array - not enough memory was allocated and data were written outside of allocated memory.
TEST_CASE("Bug #1", "[LevelD]") {
	LevelD out;
	LevelD in;

	out.mesh.layerWidth = 40;
	out.mesh.layerHeight = 40;
	out.mesh.tileWidth = 64;
	out.mesh.tileHeight = 64;
	out.mesh.layers.resize(1);

	out.mesh.layers[0].tiles.resize(out.mesh.layerWidth * out.mesh.layerHeight);
	out.mesh.layers[0].blocks.resize(out.mesh.layerWidth * out.mesh.layerHeight);

	out.things.resize(1);

	out.saveToFile("temp.lvd");
	in.loadFromFile("temp.lvd");

	assertMetadata(in, out);
	assertMesh(in, out);
	assertThings(in, out);
	assertTriggers(in, out);
}