#include <catch.hpp>
#include "../LevelD.hpp"

TEST_CASE("Everything save/load", "[LevelD]") {
	LevelD out;
	LevelD in;

	SECTION("Empty") {
		out.saveToFile("temp.lvd");
		in.loadFromFile("temp.lvd");
	}
	
	SECTION("Data") {
		out = {
			{ "MAP01", "Entryway", "doomista", "First level of the game", 1554812963 },
			{ 16, 16, 4, 4,
				{ 1, 2, 2, 3, 
				  2, 0, 0, 2, 
				  2, 0, 0, 2, 
				  4, 2, 2, 5 }, 
				{ 1, 1, 1, 1, 
				  1, 0, 0, 1, 
				  1, 0, 0, 1, 
				  1, 1, 1, 1} },
			{ {64, 128, 0} },
			{ {192, 192, 1} },
			{ {128, 64, 10}, {192, 192, 1} }
		};
		out.saveToFile("temp.lvd");
		in.loadFromFile("temp.lvd");
	}

	// Metadata asserts
	REQUIRE(in.metadata.timestamp == out.metadata.timestamp);
	REQUIRE(in.metadata.id == out.metadata.id);
	REQUIRE(in.metadata.name == out.metadata.name);
	REQUIRE(in.metadata.author == out.metadata.author);
	REQUIRE(in.metadata.description == out.metadata.description);

	// Mesh asserts
	REQUIRE(out.mesh.tileWidth == in.mesh.tileWidth);
	REQUIRE(out.mesh.tileHeight == in.mesh.tileHeight);
	REQUIRE(out.mesh.width == in.mesh.width);
	REQUIRE(out.mesh.height == in.mesh.height);
	REQUIRE(out.mesh.width *  out.mesh.height == out.mesh.tiles.size());
	REQUIRE(out.mesh.width *  out.mesh.height == out.mesh.blocks.size());

	for (unsigned i = 0; i < out.mesh.tiles.size(); i++) {
		REQUIRE(out.mesh.tiles[i] == in.mesh.tiles[i]);
		REQUIRE(out.mesh.blocks[i] == in.mesh.blocks[i]);
	}

	// Players
	REQUIRE(out.players.size() == in.players.size());

	for (unsigned i = 0; i < out.players.size(); i++) {
		REQUIRE(out.players[i].id == in.players[i].id);
		REQUIRE(out.players[i].x == in.players[i].x);
		REQUIRE(out.players[i].y == in.players[i].y);
		REQUIRE(out.players[i].flags == in.players[i].flags);
	}

	// NPCs
	REQUIRE(out.npcs.size() == in.npcs.size());

	for (unsigned i = 0; i < out.npcs.size(); i++) {
		REQUIRE(out.npcs[i].id == in.npcs[i].id);
		REQUIRE(out.npcs[i].x == in.npcs[i].x);
		REQUIRE(out.npcs[i].y == in.npcs[i].y);
		REQUIRE(out.npcs[i].flags == in.npcs[i].flags);
	}

	// Item
	REQUIRE(out.items.size() == in.items.size());

	for (unsigned i = 0; i < out.items.size(); i++) {
		REQUIRE(out.items[i].id == in.items[i].id);
		REQUIRE(out.items[i].x == in.items[i].x);
		REQUIRE(out.items[i].y == in.items[i].y);
		REQUIRE(out.items[i].flags == in.items[i].flags);
	}
}