#include <catch.hpp>
#include "../LevelD.hpp"

TEST_CASE("Players save/load", "[LevelD]") {
	LevelD out;
	LevelD in;

	SECTION("Empty") {
		out.saveToFile("temp.lvd");
		in.loadFromFile("temp.lvd");
	}

	SECTION("/w data") {
		out.players = { {1, 2, 0}, {10, 20, 30}, {244, 300, 10} };
		out.saveToFile("temp.lvd");
		in.loadFromFile("temp.lvd");
	}

	REQUIRE(out.players.size() == in.players.size());

	for (unsigned i = 0; i < out.players.size(); i++) {
		REQUIRE(out.players[i].id == in.players[i].id);
		REQUIRE(out.players[i].x == in.players[i].x);
		REQUIRE(out.players[i].y == in.players[i].y);
		REQUIRE(out.players[i].flags == in.players[i].flags);
	}
}

TEST_CASE("NPCs save/load", "[LevelD]") {
	LevelD out;
	LevelD in;

	SECTION("Empty") {
		out.saveToFile("temp.lvd");
		in.loadFromFile("temp.lvd");
	}

	SECTION("/w data") {
		out.npcs = { {1, 2, 0}, {10, 20, 30}, {244, 300, 10} };
		out.saveToFile("temp.lvd");
		in.loadFromFile("temp.lvd");
	}

	REQUIRE(out.npcs.size() == in.npcs.size());

	for (unsigned i = 0; i < out.npcs.size(); i++) {
		REQUIRE(out.npcs[i].id == in.npcs[i].id);
		REQUIRE(out.npcs[i].x == in.npcs[i].x);
		REQUIRE(out.npcs[i].y == in.npcs[i].y);
		REQUIRE(out.npcs[i].flags == in.npcs[i].flags);
	}
}

TEST_CASE("Items save/load", "[LevelD]") {
	LevelD out;
	LevelD in;

	SECTION("Empty") {
		out.saveToFile("temp.lvd");
		in.loadFromFile("temp.lvd");
	}

	SECTION("/w data") {
		out.items = { {1, 2, 0}, {10, 20, 30}, {244, 300, 10} };
		out.saveToFile("temp.lvd");
		in.loadFromFile("temp.lvd");
	}

	REQUIRE(out.items.size() == in.items.size());

	for (unsigned i = 0; i < out.items.size(); i++) {
		REQUIRE(out.items[i].id == in.items[i].id);
		REQUIRE(out.items[i].x == in.items[i].x);
		REQUIRE(out.items[i].y == in.items[i].y);
		REQUIRE(out.items[i].flags == in.items[i].flags);
	}
}