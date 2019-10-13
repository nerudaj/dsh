#include "Perlin.hpp"
#include "Vector.hpp"
#include "VectorMath.hpp"
#include "Generate.hpp"

using perlin::RawNoiseGenerator;

void RawNoiseGenerator::generateGradients(const unsigned dimensions) {
	std::mt19937 generator(seed);

	for (auto &grad : gradients) {
		grad = generateGradient(complexity, generator, dimensions);
	}
}

std::vector<float> RawNoiseGenerator::computeDotProducts(const VectorFloat &point, int pointIndex) const {
	auto pointBounds = Math::getPointBoundingBox(pointIndex, gridSize);

	std::vector<float> result;

	for (auto &gradIndex : pointBounds) {
		auto &gradient = gradients[gradIndex];

		auto gradientOrigin = Math::vectorFromIndex(pointIndex, gridSize);
		auto vecToPoint = VectorMath::getVectorFromPoints(point, gradientOrigin);

		result.push_back(VectorMath::getDotProduct(vecToPoint, gradient));
	}

	return result;
}

float RawNoiseGenerator::getValueAt(const std::vector<int> &point) const {
	VectorFloat offsetPoint = Convert::vecIntToOffsetedFloat(point, gridDensity);
	VectorInt flooredPoint = Convert::vecFloatToInt(offsetPoint);

	VectorFloat lerpFactors = Math::computeLerpFactors(flooredPoint, offsetPoint);

	int index = Math::getSquashedIndex(flooredPoint, gridSize);

	auto dotProducts = computeDotProducts(offsetPoint, index);

	return Math::reduceDotProducts(dotProducts, lerpFactors);
}