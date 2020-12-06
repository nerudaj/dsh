#include <catch.hpp>
#include "Assertions.hpp"

void assertMetadata(const LevelD &in, const LevelD &out) {
	REQUIRE(in.metadata.timestamp == out.metadata.timestamp);
	REQUIRE(in.metadata.id == out.metadata.id);
	REQUIRE(in.metadata.name == out.metadata.name);
	REQUIRE(in.metadata.author == out.metadata.author);
	REQUIRE(in.metadata.description == out.metadata.description);
}

void assertMesh(const LevelD &in, const LevelD &out) {
	REQUIRE(out.mesh.empty() == in.mesh.empty());
	REQUIRE(out.mesh.tileWidth == in.mesh.tileWidth);
	REQUIRE(out.mesh.tileHeight == in.mesh.tileHeight);
	REQUIRE(out.mesh.layerWidth == in.mesh.layerWidth);
	REQUIRE(out.mesh.layerHeight == in.mesh.layerHeight);
	REQUIRE(out.mesh.layers.size() == in.mesh.layers.size());

	for (unsigned i = 0; i < out.mesh.layers.size(); i++) {
		auto &inLayer = in.mesh.layers[i];
		auto &outLayer = out.mesh.layers[i];

		REQUIRE(in.mesh.layerWidth * in.mesh.layerHeight == inLayer.tiles.size());
		REQUIRE(inLayer.tiles.size() == inLayer.blocks.size());

		for (unsigned j = 0; j < outLayer.tiles.size(); j++) {
			REQUIRE(outLayer.tiles[j] == inLayer.tiles[j]);
			REQUIRE(outLayer.blocks[j] == inLayer.blocks[j]);
		}
	}
}

void assertThings(const LevelD &in, const LevelD &out) {
	REQUIRE(out.things.size() == in.things.size());

	for (unsigned i = 0; i < out.things.size(); i++) {
		REQUIRE(out.things[i].id == in.things[i].id);
		REQUIRE(out.things[i].tag == in.things[i].tag);
		REQUIRE(out.things[i].x == in.things[i].x);
		REQUIRE(out.things[i].y == in.things[i].y);
		REQUIRE(out.things[i].flags == in.things[i].flags);
		REQUIRE(out.things[i].metadata == in.things[i].metadata);
	}
}

void assertTriggers(const LevelD &in, const LevelD &out) {
	REQUIRE(out.triggers.size() == in.triggers.size());

	for (unsigned i = 0; i < out.triggers.size(); i++) {
		const LevelD::Trigger &inTrig = in.triggers[i];
		const LevelD::Trigger &outTrig = out.triggers[i];

		REQUIRE(inTrig.x == outTrig.x);
		REQUIRE(inTrig.y == outTrig.y);
		REQUIRE(inTrig.areaType == outTrig.areaType);
		REQUIRE(inTrig.radius == outTrig.radius);
		REQUIRE(inTrig.width == outTrig.width);
		REQUIRE(inTrig.height == outTrig.height);
		REQUIRE(inTrig.id == outTrig.id);
		REQUIRE(inTrig.tag == outTrig.tag);
		REQUIRE(inTrig.type == outTrig.type);
		REQUIRE(inTrig.a1 == outTrig.a1);
		REQUIRE(inTrig.a2 == outTrig.a2);
		REQUIRE(inTrig.a3 == outTrig.a3);
		REQUIRE(inTrig.a4 == outTrig.a4);
		REQUIRE(inTrig.a5 == outTrig.a5);
		REQUIRE(inTrig.metadata == outTrig.metadata);
	}
}
