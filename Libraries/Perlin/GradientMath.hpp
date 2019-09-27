#pragma once

#include <cmath>
#include "Perlin.hpp"

namespace perlin {

class GradientMath {
public:
	template<unsigned Dimensions>
	static float getGradientSize(const Gradient<Dimensions> &vec) {
		float sum = 0.f;

		for (unsigned i = 0; i < Dimensions; i++) {
			sum += vec[i] * vec[i];
		}

		return sum == 0.f ? sum : sqrt(sum);
	}

	template<unsigned Dimensions>
	static void normalizeGradient(Gradient<Dimensions> &vec) {
		float size = getGradientSize(vec);
		if (size == 0.f) return;

		for (unsigned i = 0; i < Dimensions; i++) {
			vec[i] /= size;
		}
	}

	template<unsigned Dimensions>
	static float getGradientDotProduct(Gradient<Dimensions> &vec1, Gradient<Dimensions> &vec2) {
		return -1.f;
	}

	static float lerp(float a, float b, float t) {
		return (1.f - t) * a + t * b;
	}
};

}