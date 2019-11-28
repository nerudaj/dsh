#include <catch.hpp>
#include "../Math.hpp"

using perlin::Math;
using perlin::VectorInt;
using perlin::VectorFloat;

TEST_CASE("lerp", "[Math]") {
	REQUIRE(Math::lerp(0.f, 1.f, 0.5f) == 0.5f);
	REQUIRE(Math::lerp(10.f, 20.f, 0.f) == 10.f);
	REQUIRE(Math::lerp(10.f, 20.f, 1.f) == 20.f);
	REQUIRE(Math::lerp(10.f, 20.f, 0.5f) == 15.f);
	REQUIRE(Math::lerp(10.f, 20.f, 0.75f) == 17.5f);
}

TEST_CASE("getDimensionsProduct", "[Math]") {
	REQUIRE(Math::getDimensionsProduct({0, 0, 0}) == 0);
	REQUIRE(Math::getDimensionsProduct({1}) == 1);
	REQUIRE(Math::getDimensionsProduct({2}) == 2);
	REQUIRE(Math::getDimensionsProduct({1, 2, 3}) == 6);
}

TEST_CASE("getSquashedIndex", "[Math]") {
	SECTION("Zero vector") {
		REQUIRE(Math::getSquashedIndex({0, 0, 0}, {10, 10, 10}) == 0);
	}

	SECTION("One dimension") {
		REQUIRE(Math::getSquashedIndex({1}, {3}) == 1);
		REQUIRE(Math::getSquashedIndex({3}, {3}) == 1);
	}

	SECTION("Two dimensions") {
		REQUIRE(Math::getSquashedIndex({1, 0}, {4, 4}) == 1);
		REQUIRE(Math::getSquashedIndex({2, 2}, {4, 4}) == 10);
		REQUIRE(Math::getSquashedIndex({3, 1}, {4, 4}) == 4);
		REQUIRE(Math::getSquashedIndex({3, 3}, {4, 4}) == 0);
	}

	SECTION("Three dimensions") {
		REQUIRE(Math::getSquashedIndex({1, 1, 1}, {2, 2, 2}) == 0);
	}

	SECTION("Four dimensions") {
		REQUIRE(Math::getSquashedIndex({1, 1, 1, 1}, {2, 2, 2, 2}) == 0);
	}
}

TEST_CASE("getPointBoundingBox", "[Math]") {
	SECTION("One dimension") {
		auto data = Math::getPointBoundingBox(0, {10});

		REQUIRE(data.size() == 2);
		REQUIRE(data[0] == 0);
		REQUIRE(data[1] == 1);
	}

	SECTION("Two dimensions") {
		auto data = Math::getPointBoundingBox(0, {10, 10});

		REQUIRE(data.size() == 4);
		REQUIRE(data[0] == 0);
		REQUIRE(data[1] == 1);
		REQUIRE(data[2] == 10);
		REQUIRE(data[3] == 11);
	}

	SECTION("Three dimensions") {
		auto data = Math::getPointBoundingBox(0, {10, 10, 10});

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
		auto data = Math::getPointBoundingBox(0, {10, 10, 10, 10});

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

TEST_CASE("computeLerpFactors", "[Math]") {
	auto factors = Math::computeLerpFactors({1, 2, 2}, {1.5f, 2.25f, 2.75f});

	REQUIRE(factors[0] == Approx(0.5f));
	REQUIRE(factors[1] == Approx(0.25f));
	REQUIRE(factors[2] == Approx(0.75f));
}

TEST_CASE("vectorFromIndex", "[Math]") {
	auto grad = Math::vectorFromIndex(321, {10, 10, 10});

	REQUIRE(grad[0] == 1.f);
	REQUIRE(grad[1] == 2.f);
	REQUIRE(grad[2] == 3.f);
}

TEST_CASE("reduceDotProducts", "[Math]") {
	float result = Math::reduceDotProducts({0.f, 1.f}, {0.5f});
	REQUIRE(result == Approx(0.5f));

	result = Math::reduceDotProducts({0.f, 1.f, 2.f, 3.f}, {0.5f, 0.25f});
	REQUIRE(result == Approx(1.f));

	result = Math::reduceDotProducts({0.f, 1.f, 2.f, 3.f, 4.f, 5.f, 6.f, 7.f}, {0.5f, 0.25f, 0.75f});
	REQUIRE(result == Approx(4.f));
}