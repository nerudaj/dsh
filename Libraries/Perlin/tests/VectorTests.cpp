#include <catch.hpp>
#include "../Perlin.hpp"
#include "../Vector.hpp"

TEST_CASE("getNormalizedIndex zero test", "[Vector]") {
	perlin::Vector<3> vec({0, 0, 0});
	int out = vec.getNormalizedIndex({{10, 10, 10}});
	REQUIRE(out == 0);
}

TEST_CASE("getNormalizedIndex one dimension test", "[Vector]") {
	SECTION("2-10") {
		perlin::Vector<1> vec({2});
		int out = vec.getNormalizedIndex({{10}});
		REQUIRE(out == 2);
	}

	SECTION("overflow 2-1") {
		perlin::Vector<1> vec({2});
		int out = vec.getNormalizedIndex({{1}});
		REQUIRE(out == 0);
	}

	SECTION("overflow 10-7") {
		perlin::Vector<1> vec({10});
		int out = vec.getNormalizedIndex({{7}});
		REQUIRE(out == 3);
	}
}

TEST_CASE("getNormalizedIndex multi dim test", "[Vector]") {
	SECTION("1,1-2,2") {
		perlin::Vector<2> vec({1, 1});
		int out = vec.getNormalizedIndex({{2, 2}});
		REQUIRE(out == 3);
	}

	SECTION("5,1-10,10") {
		perlin::Vector<2> vec({5, 1});
		int out = vec.getNormalizedIndex({{10, 10}});
		REQUIRE(out == 15);
	}

	SECTION("5,1-1,1") {
		perlin::Vector<2> vec({5, 1});
		int out = vec.getNormalizedIndex({{1, 1}});
		REQUIRE(out == 0);
	}

	SECTION("1,1,1-2,2,2") {
		perlin::Vector<3> vec({1, 1, 1});
		int out = vec.getNormalizedIndex({{2, 2, 2}});
		REQUIRE(out == 7);
	}

	SECTION("1,1,1,1-2,2,2,2") {
		perlin::Vector<4> vec({1, 1, 1, 1});
		int out = vec.getNormalizedIndex({{2, 2, 2, 2}});
		REQUIRE(out == 15);
	}
}
