#pragma once

#include <random>

#include "Perlin.hpp"
#include "VectorMath.hpp"

namespace perlin {

VectorFloat generateGradientSlowRadial(std::mt19937 &generator, const unsigned dimensions) {
	std::uniform_real_distribution<float> distribution(-1.f, 1.f);

	VectorFloat result(dimensions);

	for (auto &dim : result) {
		dim = distribution(generator);
	}

	VectorMath::normalize(result);

	return result;
}

VectorFloat generateGradient(GradientComplexity complexity, std::mt19937 &generator, const unsigned dimensions) {
	switch (complexity) {
	case GradientComplexity::SlowRadial:
		return generateGradientSlowRadial(generator, dimensions);
		break;

	default:
		throw std::runtime_error("Invalid complexity used!");
	}
}

}