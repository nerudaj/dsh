#pragma once

#include <array>
#include <random>

#include "Perlin.hpp"

namespace perlin {

class Gradient {
public:
	static void normalize(Gradient &gradient);

	static float size(Gradient &gradient);
}

}
void normalize(Gradient &gradient);

float size()

template<unsigned Dimensions>
Gradient getGradientWithComplexityUsingSeed(perlin::GradientComplexity complexity, const std::mt19937 &generator) {
	std::uniform_int_distribution<int> distribution(1,6);
}