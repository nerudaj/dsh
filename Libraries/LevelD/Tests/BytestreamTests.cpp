#include <catch.hpp>
#include <iostream>
#include "../Bytestream/Bytestream.hpp"

TEMPLATE_TEST_CASE("Bytestream UintT", "[Bytestream]", uint8_t, uint16_t, uint32_t, uint64_t) {
	TestType value;
	TestType in;

	SECTION("zero") {
		value = 0;
	}

	SECTION("half") {
		value = TestType(-1) / 2;
	}

	SECTION("max") {
		value = -1;
	}

	BytestreamOut save("bs");
	save << value;
	save.close();

	BytestreamIn load("bs");
	load >> in;

	REQUIRE(value == in);
}

TEST_CASE("Bytestream string", "[Bytestream]") {
	std::string out;
	std::string in;

	SECTION("empty") {
		out = "";
	}

	SECTION("single word") {
		out = "doomista";
	}

	SECTION("Multi word") {
		out = "Multi word description of the level.";
	}

	BytestreamOut save("bs");
	save << out;
	save.close();

	BytestreamIn load("bs");
	load >> in;

	REQUIRE(out == in);
}

TEST_CASE("Bytestream vector16", "[Bytestream]") {
	std::vector<uint16_t> out;
	std::vector<uint16_t> in;

	SECTION("empty") {
		out = {};
	}

	SECTION("small numbers") {
		out = {1, 2, 3, 4, 5};
	}

	SECTION("big numbers") {
		out = {69, 42, 1, 0, 256, 0xffff, 4096};
	}

	BytestreamOut save("bs");
	save << out;
	save.close();

	BytestreamIn load("bs");
	load >> in;

	REQUIRE(out.size() == in.size());
	for (unsigned i = 0; i < out.size(); i++) {
		REQUIRE(out[i] == in[i]);
	}
}