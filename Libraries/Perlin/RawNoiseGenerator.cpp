#include "Perlin.hpp"
#include "Vector.hpp"
#include "VectorMath.hpp"
#include "Generate.hpp"
#include <cassert>
#include <iostream>

using perlin::RawNoiseGenerator;

void RawNoiseGenerator::generateGradients(const unsigned dimensions) {
	std::mt19937 generator(seed);

	assert(gridSize.size() == dimensions);

	for (auto &grad : gradients) {
		grad = generateGradient(complexity, generator, dimensions);
		assert(grad.size() == gridSize.size());
	}
}

std::vector<float> RawNoiseGenerator::computeDotProducts(const VectorFloat &point, int pointIndex) const {
	auto pointBounds = Math::getPointBoundingBox(pointIndex, gridSize);

	std::vector<float> result;

	for (auto &gradIndex : pointBounds) {
		//std::cout << "index: " << gradIndex << std::endl;
		auto &gradient = gradients[gradIndex];

		assert(gradient.size() == gridSize.size());

		auto gradientOrigin = Math::vectorFromIndex(pointIndex, gridSize);
		auto vecToPoint = VectorMath::getVectorFromPoints(point, gradientOrigin);

		assert(gradientOrigin.size() == gradient.size());
		assert(gradientOrigin.size() == vecToPoint.size());
		assert(gradient.size() == vecToPoint.size());

		result.push_back(VectorMath::getDotProduct(vecToPoint, gradient));
	}

	assert(result.size() == pointBounds.size());

	return result;
}

float RawNoiseGenerator::getValueAtRaw(const VectorInt &point) const {
	/*std::cout << "source: ";
	for (auto &dim : point) {
		std::cout << dim << ",";
	}
	std::cout << std::endl;*/
	VectorFloat offsetPoint = Convert::vecIntToOffsetedFloat(point, gridSize, gridDensity);
	/*std::cout << "offset: ";
	for (auto &dim : offsetPoint) {
		std::cout << dim << ",";
	}
	std::cout << std::endl;*/
	VectorInt flooredPoint = Convert::vecFloatToInt(offsetPoint);
	/*std::cout << "floored: ";
	for (auto &dim : flooredPoint) {
		std::cout << dim << ",";
	}
	std::cout << std::endl;*/

	VectorFloat lerpFactors = Math::computeLerpFactors(flooredPoint, offsetPoint);

	int index = Math::getSquashedIndex(flooredPoint, gridSize);

	auto dotProducts = computeDotProducts(offsetPoint, index);

	return Math::reduceDotProducts(dotProducts, lerpFactors);
}