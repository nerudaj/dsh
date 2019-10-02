#pragma once

#include "Perlin.hpp"

using namespace perlin;

template<unsigned Dimensions>
int Vector<Dimensions>::getNormalizedIndex(const Vector<Dimensions> &dims) const {
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

template<unsigned Dimensions>
int Vector<Dimensions>::getDimsProduct() const {
	int result = 1;

	for (auto &dim : data) {
		result *= dim;
	}

	return result;
}

template<unsigned Dimensions>
void Vector<Dimensions>::normalizeDims(const Vector<Dimensions> &other) {
	for (unsigned i = 0; i < Dimensions; i++) {
		data[i] /= other[i];
	}
}