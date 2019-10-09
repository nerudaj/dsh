#include <catch.hpp>
#include "../Math.hpp"

TEST_CASE("lerp", "[Math]") {
	REQUIRE(Math::lerp(10.f, 20.f, 0.f) == 10.f);
	REQUIRE(Math::lerp(10.f, 20.f, 1.f) == 20.f);
	REQUIRE(Math::lerp(10.f, 20.f, 0.5f) == 15.f);
	REQUIRE(Math::lerp(10.f, 20.f, 0.75f) == 17.5f);
}

TEST_CASE("getDimensionsProduct", "[Math]") {
	REQUIRE(false);
}

TEST_CASE("getSquashedIndex", "[Math]") {
	REQUIRE(false);
}

/*
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
*/

TEST_CASE("getPointBoundingBox", "[Math]") {
	REQUIRE(false);
}

/*
TEST_CASE("Get gradient indices", "[GradientMath]") {
	SECTION("One dimension") {
		auto data = GradientMath::getGradientIndices<1>(0, {{10}});

		REQUIRE(data.size() == 2);
		REQUIRE(data[0] == 0);
		REQUIRE(data[1] == 1);
	}

	SECTION("Two dimensions") {
		auto data = GradientMath::getGradientIndices<2>(0, {{10, 10}});

		REQUIRE(data.size() == 4);
		REQUIRE(data[0] == 0);
		REQUIRE(data[1] == 1);
		REQUIRE(data[2] == 10);
		REQUIRE(data[3] == 11);
	}

	SECTION("Three dimensions") {
		auto data = GradientMath::getGradientIndices<3>(0, {{10, 10, 10}});

		REQUIRE(data.size() == 8);
		REQUIRE(data[0] == 0);
		REQUIRE(data[1] == 1);
		REQUIRE(data[2] == 10);
		REQUIRE(data[3] == 11);
		REQUIRE(data[4] == 100);
		REQUIRE(data[5] == 101);
		REQUIRE(data[6] == 110);
		REQUIRE(data[7] == 111);
	}

	SECTION("Four dimensions") {
		auto data = GradientMath::getGradientIndices<4>(0, {{10, 10, 10, 10}});

		REQUIRE(data.size() == 16);
		REQUIRE(data[0] == 0);
		REQUIRE(data[1] == 1);
		REQUIRE(data[2] == 10);
		REQUIRE(data[3] == 11);
		REQUIRE(data[4] == 100);
		REQUIRE(data[5] == 101);
		REQUIRE(data[6] == 110);
		REQUIRE(data[7] == 111);
		REQUIRE(data[8] == 1000);
		REQUIRE(data[9] == 1001);
		REQUIRE(data[10] == 1010);
		REQUIRE(data[11] == 1011);
		REQUIRE(data[12] == 1100);
		REQUIRE(data[13] == 1101);
		REQUIRE(data[14] == 1110);
		REQUIRE(data[15] == 1111);
	}
}
*/