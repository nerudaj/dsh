#include <catch.hpp>
#include "../Perlin.hpp"
#include "../GradientMath.hpp"

using perlin::GradientMath;

TEST_CASE("Get gradient size", "[GradientMath]") {
	SECTION("Zero gradient size") {
		REQUIRE(GradientMath::getGradientSize<1>({0}) == 0.f);
		REQUIRE(GradientMath::getGradientSize<2>({0, 0}) == 0.f);
		REQUIRE(GradientMath::getGradientSize<3>({0, 0, 0}) == 0.f);
		REQUIRE(GradientMath::getGradientSize<4>({0, 0, 0, 0}) == 0.f);
	}

	SECTION("All ones") {
		REQUIRE(GradientMath::getGradientSize<1>({1}) == 1.f);
		REQUIRE(GradientMath::getGradientSize<2>({1, 1}) == Approx(1.414214f));
		REQUIRE(GradientMath::getGradientSize<3>({1, 1, 1}) == Approx(1.732051f));
		REQUIRE(GradientMath::getGradientSize<4>({1, 1, 1, 1}) == 2.f);
	}

	SECTION("Complex values") {
		REQUIRE(GradientMath::getGradientSize<1>({-1.f}) == 1.f);
		REQUIRE(GradientMath::getGradientSize<2>({10, -10}) == Approx(14.142136f));
		REQUIRE(GradientMath::getGradientSize<3>({3, 4, 5}) == Approx(7.071068f));
		REQUIRE(GradientMath::getGradientSize<4>({1, 1, 1, 1}) == 2.f);
	}
}
