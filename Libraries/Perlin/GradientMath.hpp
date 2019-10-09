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

	template<unsigned Dimensions>
	static Gradient<Dimensions> makeGradientFromCoord(const Vector<Dimensions> &coord, const Vector<Dimensions> &normalFactor) {
		Gradient<Dimensions> result;

		for (unsigned i = 0; i < Dimensions; i++) {
			// 0.5f offsets coordinate to the middle of the tile
			result[i] = (coord.getDim(i) + 0.5f) / normalFactor.getDim(i);
		}

		return result;
	}
	
	template<unsigned Dimensions>
	static Vector<Dimensions> makeVectorFromGradient(const Gradient<Dimensions> &grad) {
		std::array<int, Dimensions> result;

		for (unsigned i = 0; i < Dimensions; i++) {
			result[i] = static_cast<int>(grad[i]);
		}

		return Vector<Dimensions>(result);
	}
	
	template<unsigned Dimensions>
	static Gradient<Dimensions>constructGradientFromPoints(const Gradient<Dimensions> &from, const Gradient<Dimensions> &to) {
		Gradient<Dimensions> result;

		for (unsigned  i = 0; i < Dimensions; i++) {
			result[i] = to[i] - from[i];
		}

		return result;
	}
	
	template<unsigned Dimensions>
	static std::vector<int> getGradientIndices(int start, const Vector<Dimensions> &dims) {
		std::vector<int> result = { start, start + 1 };

		for (unsigned i = 1; i < Dimensions; i++) {
			unsigned limit = result.size();
			unsigned offset = 1;

			for (unsigned p = 0, j = i - 1; p < i; p++, j--) {
				offset *= dims.getDim(j);
			}

			for (unsigned p = 0; p < limit; p++) {
				result.push_back(result[p] + offset);
			}
		}

		return result;
	}
};

}