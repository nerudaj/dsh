#pragma once

#include <cmath>
#include "Perlin.hpp"

namespace perlin {

class GradientMath {
public:
	template<unsigned Dimensions>
	static Gradient<Dimensions> makeGradientFromCoord(const Vector<Dimensions> &coord, const Vector<Dimensions> &normalFactor) {
		Gradient<Dimensions> result;

		for (unsigned i = 0; i < Dimensions; i++) {
			// 0.5f offsets coordinate to the middle of the tile
			result[i] = (coord.getDim(i) + 0.5f) / normalFactor.getDim(i);
		}

		return result;
	}
};

}