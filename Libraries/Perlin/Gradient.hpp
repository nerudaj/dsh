#pragma once

#include <array>
#include <random>

#include "Perlin.hpp"

template<unsigned Dimensions>
Gradient getGradientWithComplexityUsingSeed(perlin::GradientComplexity complexity, const std::mt19937 &generator) {
	std::uniform_int_distribution<int> distribution(1,6);
}