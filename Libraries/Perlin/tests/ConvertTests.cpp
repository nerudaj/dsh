#include <catch.hpp>
#include "../Convert.hpp"

using perlin::Convert;
using perlin::VectorInt;
using perlin::VectorFloat;

TEST_CASE("vecIntToFloat", "[Convert]") {
	SECTION("One dimension") {
		auto vec = Convert::vecIntToOffsetedFloat({3}, {2});
		REQUIRE(vec[0] == 1.75f);

		vec = Convert::vecIntToOffsetedFloat({2}, {2});
		REQUIRE(vec[0] == 1.25f);
	}

	SECTION("Two dimensions") {
		auto vec = Convert::vecIntToOffsetedFloat({3, 10}, {2, 2});
		REQUIRE(vec[0] == 1.75f);
		REQUIRE(vec[1] == 5.25f);
	}
}

TEST_CASE("vecFloatToInt", "[Convert]") {
	SECTION("Two dimensions") {
		auto vec = Convert::vecFloatToInt({2.25f, 7.75f});
		REQUIRE(vec[0] == 2);
		REQUIRE(vec[1] == 7);
	}
}