#include "Perlin.hpp"
#include <iostream>

template<unsigned Dimensions>
int perlin::Vector<Dimensions>::getNormalizedIndex(const perlin::Vector<Dimensions> &dims) const {
	int result = 0;

	for (unsigned i = 0; i < Dimensions; i++) {
		int normalizedDataI = data.at(i) % dims.data.at(i);
		int dataMultiplicator = 1;

		for (unsigned p = 0, j = i - 1; p < i; p++, j--) {
			dataMultiplicator *= dims.data.at(j);
		}

		result += normalizedDataI * dataMultiplicator;
	}

	return result;
}