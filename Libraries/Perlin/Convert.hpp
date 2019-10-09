#pragma once

#include "Vector.hpp"

namespace perlin {

class Convert {
public:
	static VectorInt vecFloatToInt(const VectorFloat &vec) {
		return VectorInt(vec.begin(), vec.end());
	}

	static VectorFloat vecIntToFloat(const VectorInt &vec) {
		return VectorFloat(vec.begin(), vec.end());
	}
};

}