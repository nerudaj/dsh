#include "Perlin.hpp"

using namespace perlin;

template<unsigned Dimensions>
void NoiseGenerator<Dimensions>::generateGradients() {
	
}

template<unsigned Dimensions>
float NoiseGenerator<Dimensions>::getValueAt(const Vector<Dimensions> &coord) const {
	return -1.f;
}

template class NoiseGenerator<1>;
template class NoiseGenerator<2>;
template class NoiseGenerator<3>;
template class NoiseGenerator<4>;
template class NoiseGenerator<5>;