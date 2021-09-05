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

	/*SECTION("Defined big mesh") {
		const unsigned W = 450;
		const unsigned H = 270;
		out.mesh = { 64, 64, W, H, {} };
		out.mesh.layers.push_back({
			std::vector<uint16_t>(W * H, 1),
			std::vector<bool>(W * H, 1),
		});
	}*/

	out.saveToFile("temp.lvd");
	in.loadFromFile("temp.lvd");

	assertMesh(in, out);
}

/*TEST_CASE("Mesh save big", "[LevelD]") {
	LevelD out;
	LevelD in;
	
	out.mesh.layerWidth = 45;
	out.mesh.layerHeight = 27;
	out.mesh.tileWidth = 64;
	out.mesh.tileHeight = 64;
	out.mesh.layers.resize(1);
	
	out.mesh.layers[0].tiles.resize(out.mesh.layerWidth * out.mesh.layerHeight);
	out.mesh.layers[0].blocks.resize(out.mesh.layerWidth * out.mesh.layerHeight);
	out.mesh.layers[0].tiles.back() = 1;
	
	out.saveToFile("temp.lvd");
	in.loadFromFile("temp.lvd");
	
	assertMesh(in, out);
}*/
