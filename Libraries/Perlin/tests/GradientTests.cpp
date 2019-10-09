#include <catch.hpp>
#include "../Generate.hpp"

using perlin::GradientComplexity;
using perlin::VectorMath;

TEST_CASE("Generate gradient", "[Gradient]") {
	std::mt19937 generator(0);

	SECTION("Test normality of gradients") {
		for (unsigned i = 0; i < 20; i++) {
			auto grad = perlin::generateGradient(GradientComplexity::SlowRadial, generator, 3);
			
			REQUIRE(VectorMath::getSize(grad) == Approx(1.f));
		}
	}

	SECTION("Test Slow Radial generate") {
		auto grad = perlin::generateGradient(GradientComplexity::SlowRadial, generator, 3);

		REQUIRE(grad[0] == Approx(0.2039f).margin(0.0001));
		REQUIRE(grad[1] == Approx(0.38783f).margin(0.00001));
		REQUIRE(grad[2] == Approx(0.89889f).margin(0.00001));
	}
}