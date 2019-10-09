#pragma once

#include "Vector.hpp"

namespace perlin {

class VectorMath {
public:
	static void normalize(VectorFloat &vec);

	static float getSize(const VectorFloat &vec);

	static float getDotProduct(const VectorFloat &a, const VectorFloat &b);

	static void normalizeEachDim(VectorInt &target, VectorInt &coefs);

	static VectorFloat getVectorFromPoints(const VectorFloat &from, const VectorFloat &to);
};

VectorFloat operator+(VectorFloat a, const VectorFloat &b);

VectorInt operator+(VectorInt a, const VectorInt &b);

}
