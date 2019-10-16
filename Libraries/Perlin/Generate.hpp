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

VectorFloat generateGradientFastOrthogonal(std::mt19937 &generator, const unsigned dimensions) {
	std::uniform_int_distribution<int> distr1(0, dimensions);

	VectorFloat result(dimensions, 0);
	result[distr1(generator)] = distr1(generator) % 2 ? 1.f : -1.f;

	return result;
}

VectorFloat generateGradient(GradientComplexity complexity, std::mt19937 &generator, const unsigned dimensions) {
	switch (complexity) {
	case GradientComplexity::SlowRadial:
		return generateGradientSlowRadial(generator, dimensions);
		break;
	
	case GradientComplexity::FastOrthogonal:
		return generateGradientFastOrthogonal(generator, dimensions);
		break;

	default:
		throw std::runtime_error("Invalid complexity used!");
	}
}

}