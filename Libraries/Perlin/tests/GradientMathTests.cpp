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

TEST_CASE("Normalize gradient", "[GradientMath]") {
	SECTION("All zeroes") {
		perlin::Gradient<1> gz1({0});
		GradientMath::normalizeGradient<1>(gz1);
		REQUIRE(GradientMath::getGradientSize<1>(gz1) == 0.f);

		perlin::Gradient<2> gz2({0, 0});
		GradientMath::normalizeGradient<2>(gz2);
		REQUIRE(GradientMath::getGradientSize<2>(gz2) == 0.f);

		perlin::Gradient<3> gz3({0, 0, 0});
		GradientMath::normalizeGradient<3>(gz3);
		REQUIRE(GradientMath::getGradientSize<3>(gz3) == 0.f);

		perlin::Gradient<4> gz4({0, 0, 0, 0});
		GradientMath::normalizeGradient<4>(gz4);
		REQUIRE(GradientMath::getGradientSize<4>(gz4) == 0.f);
	}

	SECTION("Already normalized") {
		perlin::Gradient<1> gz1({1});
		GradientMath::normalizeGradient<1>(gz1);
		REQUIRE(GradientMath::getGradientSize<1>(gz1) == 1.f);

		perlin::Gradient<2> gz2({0, 1});
		GradientMath::normalizeGradient<2>(gz2);
		REQUIRE(GradientMath::getGradientSize<2>(gz2) == 1.f);

		perlin::Gradient<3> gz3({0, 1, 0});
		GradientMath::normalizeGradient<3>(gz3);
		REQUIRE(GradientMath::getGradientSize<3>(gz3) == 1.f);

		perlin::Gradient<4> gz4({1, 0, 0, 0});
		GradientMath::normalizeGradient<4>(gz4);
		REQUIRE(GradientMath::getGradientSize<4>(gz4) == 1.f);
	}

	SECTION("Will be normalized") {
		perlin::Gradient<1> gz1({10});
		GradientMath::normalizeGradient<1>(gz1);
		REQUIRE(GradientMath::getGradientSize<1>(gz1) == Approx(1.f));

		perlin::Gradient<2> gz2({0.5, 1});
		GradientMath::normalizeGradient<2>(gz2);
		REQUIRE(GradientMath::getGradientSize<2>(gz2) == Approx(1.f));

		perlin::Gradient<3> gz3({0.25, 0.1, 0.3});
		GradientMath::normalizeGradient<3>(gz3);
		REQUIRE(GradientMath::getGradientSize<3>(gz3) == Approx(1.f));

		perlin::Gradient<4> gz4({100.f, 50.f, 69.f, 42.f});
		GradientMath::normalizeGradient<4>(gz4);
		REQUIRE(GradientMath::getGradientSize<4>(gz4) == Approx(1.f));
	}
}

TEST_CASE("Get gradient dot product", "[GradientMath]") {
	REQUIRE(GradientMath::getGradientDotProduct<1>({0.f}, {0.f}) == 0.f);
	REQUIRE(GradientMath::getGradientDotProduct<1>({1.f}, {0.f}) == 0.f);
	REQUIRE(GradientMath::getGradientDotProduct<1>({0.f}, {1.f}) == 0.f);
	REQUIRE(GradientMath::getGradientDotProduct<1>({1.f}, {1.f}) == 1.f);
	REQUIRE(GradientMath::getGradientDotProduct<1>({2.f}, {2.f}) == 4.f);
	REQUIRE(GradientMath::getGradientDotProduct<2>({1.f, 1.f}, {1.f, 2.f}) == 3.f);
	REQUIRE(GradientMath::getGradientDotProduct<2>({2.f, 1.f}, {1.f, 2.f}) == 4.f);
	REQUIRE(GradientMath::getGradientDotProduct<3>({1.f, 2.f, 3.f}, {1.f, 2.f, 3.f}) == 14.f);
	REQUIRE(GradientMath::getGradientDotProduct<4>({1.f, 2.f, 3.f, 4.f}, {1.f, 2.f, 3.f, 4.f}) == 30.f);
}

TEST_CASE("Linear interpolation", "[GradientMath]") {
	REQUIRE(GradientMath::lerp(10.f, 20.f, 0.f) == 10.f);
	REQUIRE(GradientMath::lerp(10.f, 20.f, 1.f) == 20.f);
	REQUIRE(GradientMath::lerp(10.f, 20.f, 0.5f) == 15.f);
	REQUIRE(GradientMath::lerp(10.f, 20.f, 0.75f) == 17.5f);
}

TEST_CASE("Make gradient from coord", "[GradientMath]") {
	SECTION("One dimensions") {
		auto grad = GradientMath::makeGradientFromCoord<1>({{3}}, {{2}});
		REQUIRE(grad[0] == 1.75f);

		grad = GradientMath::makeGradientFromCoord<1>({{2}}, {{2}});
		REQUIRE(grad[0] == 1.25f);
	}

	SECTION("Two dimensions") {
		auto grad = GradientMath::makeGradientFromCoord<2>({{3, 10}}, {{2, 2}});
		REQUIRE(grad[0] == 1.75f);
		REQUIRE(grad[1] == 5.25f);
	}
}

TEST_CASE("Make vector from gradient", "[GradientMath]") {
	SECTION("Two dimensions") {
		auto vec = GradientMath::makeVectorFromGradient<2>({2.25f, 7.75f});
		REQUIRE(vec.getDim(0) == 2);
		REQUIRE(vec.getDim(1) == 7);
	}
}

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

TEST_CASE("Construct gradient from points", "[GradientMath]") {
	SECTION("One dimension") {
		auto grad = GradientMath::constructGradientFromPoints<1>({1}, {2});

		REQUIRE(grad[0] == 1);
	}

	SECTION("Two dimensions") {
		auto grad = GradientMath::constructGradientFromPoints<2>({1, 0}, {2, 3});

		REQUIRE(grad[0] == 1);
		REQUIRE(grad[1] == 3);
	}

	SECTION("Three dimensions") {
		auto grad = GradientMath::constructGradientFromPoints<3>({1, 0, -1}, {2, 3, 2});

		REQUIRE(grad[0] == 1);
		REQUIRE(grad[1] == 3);
		REQUIRE(grad[2] == 3);
	}
}