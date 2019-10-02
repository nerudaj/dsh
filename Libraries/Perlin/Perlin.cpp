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
float NoiseGenerator<Dimensions>::getValueAt(Vector<Dimensions> coord) const {
	coord.normalizeDims(gridDensity);
	int index = coord.getNormalizedIndex(gridSize);
	
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