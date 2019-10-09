#include <catch.hpp>
#include "../Convert.hpp"

TEST_CASE("Make gradient from coord", "[VectorMath]") {
	SECTION("One dimensions") {
		auto grad = VectorMath::makeGradientFromCoord<1>({{3}}, {{2}});
		REQUIRE(grad[0] == 1.75f);

		grad = VectorMath::makeGradientFromCoord<1>({{2}}, {{2}});
		REQUIRE(grad[0] == 1.25f);
	}

	SECTION("Two dimensions") {
		auto grad = VectorMath::makeGradientFromCoord<2>({{3, 10}}, {{2, 2}});
		REQUIRE(grad[0] == 1.75f);
		REQUIRE(grad[1] == 5.25f);
	}
}

TEST_CASE("Make vector from gradient", "[VectorMath]") {
	SECTION("Two dimensions") {
		auto vec = VectorMath::makeVectorFromGradient<2>({2.25f, 7.75f});
		REQUIRE(vec.getDim(0) == 2);
		REQUIRE(vec.getDim(1) == 7);
	}
}