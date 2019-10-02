#pragma once

#include <array>
#include <random>

#include "Perlin.hpp"
#include "GradientMath.hpp"

namespace perlin {

// Partially instantiated template for SlowRadial complexity
template<unsigned Dimensions>
Gradient<Dimensions> generateGradientSlowRadial(std::mt19937 &generator) {
	std::uniform_real_distribution<float> distribution(-1.f, 1.f);

	Gradient<Dimensions> result;

	for (auto &dim : result) {
		dim = distribution(generator);
	}

	GradientMath::normalizeGradient<Dimensions>(result);

	return result;
}

template<unsigned Dimensions>
Gradient<Dimensions> generateGradient(GradientComplexity complexity, std::mt19937 &generator) {
	switch (complexity) {
	case GradientComplexity::SlowRadial:
		return generateGradientSlowRadial<Dimensions>(generator);
		break;

	default:
		throw std::runtime_error("Invalid complexity used!");
	}
}

}