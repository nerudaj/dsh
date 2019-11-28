#include <catch.hpp>
#include "../VectorMath.hpp"

using perlin::VectorMath;
using perlin::VectorInt;
using perlin::VectorFloat;

TEST_CASE("normalize", "[VectorMath]") {
	SECTION("All zeroes") {
		VectorFloat v1 = {0};
		VectorMath::normalize(v1);
		REQUIRE(VectorMath::getSize(v1) == 0.f);

		VectorFloat v2 = {0, 0};
		VectorMath::normalize(v2);
		REQUIRE(VectorMath::getSize(v2) == 0.f);

		VectorFloat v3 = {0, 0, 0};
		VectorMath::normalize(v3);
		REQUIRE(VectorMath::getSize(v3) == 0.f);

		VectorFloat v4 = {0, 0, 0, 0};
		VectorMath::normalize(v4);
		REQUIRE(VectorMath::getSize(v4) == 0.f);
	}

	SECTION("Already normalized") {
		VectorFloat gz1({1});
		VectorMath::normalize(gz1);
		REQUIRE(VectorMath::getSize(gz1) == 1.f);

		VectorFloat gz2({0, 1});
		VectorMath::normalize(gz2);
		REQUIRE(VectorMath::getSize(gz2) == 1.f);

		VectorFloat gz3({0, 1, 0});
		VectorMath::normalize(gz3);
		REQUIRE(VectorMath::getSize(gz3) == 1.f);

		VectorFloat gz4({1, 0, 0, 0});
		VectorMath::normalize(gz4);
		REQUIRE(VectorMath::getSize(gz4) == 1.f);
	}

	SECTION("Will be normalized") {
		VectorFloat gz1({10});
		VectorMath::normalize(gz1);
		REQUIRE(VectorMath::getSize(gz1) == Approx(1.f));

		VectorFloat gz2({0.5, 1});
		VectorMath::normalize(gz2);
		REQUIRE(VectorMath::getSize(gz2) == Approx(1.f));

		VectorFloat gz3({0.25, 0.1, 0.3});
		VectorMath::normalize(gz3);
		REQUIRE(VectorMath::getSize(gz3) == Approx(1.f));

		VectorFloat gz4({100.f, 50.f, 69.f, 42.f});
		VectorMath::normalize(gz4);
		REQUIRE(VectorMath::getSize(gz4) == Approx(1.f));
	}
}

TEST_CASE("getSize", "[VectorMath]") {
	SECTION("Zero gradient size") {
		REQUIRE(VectorMath::getSize({0}) == 0.f);
		REQUIRE(VectorMath::getSize({0, 0}) == 0.f);
		REQUIRE(VectorMath::getSize({0, 0, 0}) == 0.f);
		REQUIRE(VectorMath::getSize({0, 0, 0, 0}) == 0.f);
	}

	SECTION("All ones") {
		REQUIRE(VectorMath::getSize({1}) == 1.f);
		REQUIRE(VectorMath::getSize({1, 1}) == Approx(1.414214f));
		REQUIRE(VectorMath::getSize({1, 1, 1}) == Approx(1.732051f));
		REQUIRE(VectorMath::getSize({1, 1, 1, 1}) == 2.f);
	}

	SECTION("Complex values") {
		REQUIRE(VectorMath::getSize({-1.f}) == 1.f);
		REQUIRE(VectorMath::getSize({10, -10}) == Approx(14.142136f));
		REQUIRE(VectorMath::getSize({3, 4, 5}) == Approx(7.071068f));
		REQUIRE(VectorMath::getSize({1, 1, 1, 1}) == 2.f);
	}
}

TEST_CASE("getDotProduct", "[VectorMath]") {
	REQUIRE(VectorMath::getDotProduct({0.f}, {0.f}) == 0.f);
	REQUIRE(VectorMath::getDotProduct({1.f}, {0.f}) == 0.f);
	REQUIRE(VectorMath::getDotProduct({0.f}, {1.f}) == 0.f);
	REQUIRE(VectorMath::getDotProduct({1.f}, {1.f}) == 1.f);
	REQUIRE(VectorMath::getDotProduct({2.f}, {2.f}) == 4.f);
	REQUIRE(VectorMath::getDotProduct({1.f, 1.f}, {1.f, 2.f}) == 3.f);
	REQUIRE(VectorMath::getDotProduct({2.f, 1.f}, {1.f, 2.f}) == 4.f);
	REQUIRE(VectorMath::getDotProduct({1.f, 2.f, 3.f}, {1.f, 2.f, 3.f}) == 14.f);
	REQUIRE(VectorMath::getDotProduct({1.f, 2.f, 3.f, 4.f}, {1.f, 2.f, 3.f, 4.f}) == 30.f);
}

TEST_CASE("getVectorFromPoints", "[VectorMath]") {
	SECTION("One dimension") {
		auto vec = VectorMath::getVectorFromPoints({1}, {2});

		REQUIRE(vec[0] == 1);
	}

	SECTION("Two dimensions") {
		auto vec = VectorMath::getVectorFromPoints({1, 0}, {2, 3});

		REQUIRE(vec[0] == 1);
		REQUIRE(vec[1] == 3);
	}

	SECTION("Three dimensions") {
		auto vec = VectorMath::getVectorFromPoints({1, 0, -1}, {2, 3, 2});

		REQUIRE(vec[0] == 1);
		REQUIRE(vec[1] == 3);
		REQUIRE(vec[2] == 3);
	}
}

TEST_CASE("operator+", "[VectorMath]") {
	SECTION("float") {
		auto vec = VectorFloat({1.f}) + VectorFloat({0.5f});
		REQUIRE(vec[0] == Approx(1.5f));

		vec = VectorFloat({1.f, 0.25}) + VectorFloat({0.5f, 0.15f});
		REQUIRE(vec[0] == Approx(1.5f));
		REQUIRE(vec[1] == Approx(0.4f));
	}

	SECTION("int") {
		auto vec = VectorInt({1}) + VectorInt({2});
		REQUIRE(vec[0] == 3);
		
		vec = VectorInt({1, 3}) + VectorInt({5, 2});
		REQUIRE(vec[0] == 6);
		REQUIRE(vec[1] == 5);
	}
}