#pragma once

#include "Perlin.hpp"

class VecMath {
	template<typename T, unsigned Dimensions>
	static float getSize(const Vector<Dimensions> &vec) {
		float sum = 0.f;

		for (unsigned i = 0; i < Dimensions; i++) {
			sum += vec[i] * vec[i];
		}

		return sum == 0.f ? sum : sqrt(static_cast<float>(sum));
	}
};