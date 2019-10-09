#include "Perlin.hpp"
#include "Gradient.hpp"

using namespace perlin;

const unsigned WIDTH = 10;
const unsigned HEIGHT= 10;
const unsigned SEED = 0;
const GradientComplexity COMPLEXITY = GradientComplexity::SlowRadial;

template<unsigned Dimensions>
void NoiseGenerator<Dimensions>::generateGradients() {
	std::mt19937 generator(SEED);

	for (auto &grad : gradients) {
		grad = generateGradient<Dimensions>(COMPLEXITY, generator);
	}
}

template<unsigned Dimensions>
float NoiseGenerator<Dimensions>::getValueAt(Vector<Dimensions> coords) const {
	// Normalize coord using gridDensity and convert it to float vector (Gradient)
	Gradient<Dimensions> normalizedCoords = GradientMath::makeGradientFromCoord<Dimensions>(coords, gridDensity);

	// Floor coordinates 
	Vector<Dimensions> flooredCoords = GradientMath::makeVectorFromGradient<Dimensions>(normalizedCoords);

	// Compute lerp factors
	std::array<float, Dimensions> lerpFactors;
	for (unsigned i = 0; i < Dimensions; i++) {
		lerpFactors[i] = normalizedCoords[i] - static_cast<float>(flooredCoords.getDim(i));
	}

	// Get gradient normalized index
	int index = flooredCoords.getNormalizedIndex(gridSize);

	// Compute bounding box
	auto bounds = GradientMath::getGradientIndices<Dimensions>(index, gridSize);

	std::vector<float> dotProducts;
	for (auto &index : bounds) {
		auto &gradient = gradients[index];
		auto vecToPoint = GradientMath::constructGradientFromPoints<Dimensions>(normalizedCoords, gradient);

		dotProducts.push_back(GradientMath::getGradientDotProduct<Dimensions>(vecToPoint, gradient));
	}

	// For each vertex of the bounding box
	// Get gradient of that vertex
	// Compute vector from vertex to gcoord
	// Compute dot product of those two vectors

	// This leads to some sort of reduce algorithm
	// Gather values from previous step and somehow lerp them using params[0]
	
	// Gather values from previous step and somehow lerp them using params[1]
	
	// ....
	
	// Gather values from previous step and somehow lerp them using params[n]
	
	return -1.f;
}

template<unsigned Dimensions>
NoiseGenerator<Dimensions>::NoiseGenerator() : gridSize(Vector<Dimensions>(10)), gridDensity(Vector<Dimensions>(5)) {
	gradients.resize(gridSize.getDimsProduct());
	generateGradients();
}

template class NoiseGenerator<1>;
template class NoiseGenerator<2>;
template class NoiseGenerator<3>;
template class NoiseGenerator<4>;
template class NoiseGenerator<5>;