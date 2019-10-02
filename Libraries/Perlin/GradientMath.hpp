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

		for (auto &dim : vec) {
			dim /= size;
		}
	}

	template<unsigned Dimensions>
	static float getGradientDotProduct(const Gradient<Dimensions> &vec1, const Gradient<Dimensions> &vec2) {
		float result = 0.f;

		for (unsigned i = 0; i < Dimensions; i++) {
			result += vec1[i] * vec2[i];
		}

		return result;
	}

	static float lerp(float a, float b, float t) {
		return (1.f - t) * a + t * b;
	}
};

}