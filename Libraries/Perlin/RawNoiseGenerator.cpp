#include "Perlin.hpp"
#include "Vector.hpp"
#include "VectorMath.hpp"
#include "NoiseGeneratorFunctions.hpp"
#include "Generate.hpp"

const unsigned WIDTH = 10;
const unsigned HEIGHT= 10;
const unsigned SEED = 0;
const GradientComplexity COMPLEXITY = GradientComplexity::SlowRadial;

using perlin::RawNoiseGenerator;

void RawNoiseGenerator::generateGradients(const unsigned dimensions) {
	std::mt19937 generator(SEED);

	for (auto &grad : gradients) {
		grad = generateGradient(COMPLEXITY, generator, dimensions);
	}
}

float RawNoiseGenerator::getValueAt(const std::vector<int> &point) const {
	VectorFloat offsetPoint = Convert::vecIntToOffsetedFloat(point, gridDensity);
	VectorInt flooredPoint = Convert::vecFloatToInt(offsetPoint);

	// Compute lerp factors
	VectorFloat lerpFactors = perlin::computeLerpFactors(normalizedCoords, flooredPoint, Dimensions);

	// Get gradient normalized index
	int index = Math::getSquashedIndex(flooredPoint, gridSize);

	// Compute bounding box
	auto bounds = Math::getPointBoundingBox(index, gridSize);

	std::vector<float> dotProducts;
	for (auto &gradientIndex : bounds) {
		auto &gradient = gradients[gradientIndex];
		auto gradientLoc = Math::gradientFromIndex(index, gridSize);
		auto vecToPoint = VectorMath::getVectorFromPoints(offsetPoint, gradientLoc);

		dotProducts.push_back(VectorMath::getDotProduct<Dimensions>(vecToPoint, gradient));
	}

	for (unsigned t = 1, skip = 2, f = 0; t > dotProducts.size(); t *= 2, skip *= 2, f++) {
		for (unsigned i = 0; i < dotProducts.size(); i += skip) {
			dotProducts[i] = Math::lerp(dotProducts[i], dotProducts[i + t], lerpFactors[f]);
		}
	}
	
	return -1.f;
}