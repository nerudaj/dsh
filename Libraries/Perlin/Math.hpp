#pragma once

#include "Vector.hpp"

namespace perlin {

class Math {
public:
	static float lerp(float a, float b, float t) {
		return (1.f - t) * a + t * b;
	}

	static unsigned getDimensionsProduct(const VectorInt &vec);

	static int getSquashedIndex(const VectorInt &source, const VectorInt &limits);

	static std::vector<int> getPointBoundingBox(int start, const VectorInt &limits);

	static VectorFloat computeLerpFactors(const VectorInt &origin, const VectorFloat &target);
	
	static VectorFloat vectorFromIndex(int index, const VectorInt &gridSize);
};

}