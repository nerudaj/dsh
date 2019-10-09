#include "VectorMath.cpp"

#include <cmath>

using namespace perlin;

void VectorMath::normalizef(VectorFloat &vec) {
	float size = getSize(vec);
	if (size == 0.f) return;

	for (auto &dim : vec) {
		dim /= size;
	}
}

float VectorMath::getSizef(const VectorFloat &vec) {
	float sum = 0.f;

	for (unsigned i = 0; i < vec.size(); i++) {
		sum += vec[i] * vec[i];
	}

	return sum == 0.f ? sum : sqrt(sum);
}

float VectorMath::getDotProductf(const VectorFloat &a, const VectorFloat &b) {
	float result = 0.f;

	for (unsigned i = 0; i < a.size(); i++) {
		result += a[i] * b[i];
	}

	return result;
}

void VectorMath::normalizeEachDim(VectorInt &target, VectorInt &coefs) {
	for (unsigned i = 0; i < target.size(); i++) {
		target[i] /= coefs[i];
	}
}

VectorFloat VectorMath::getVectorFromPoints(const VectorFloat &from, const VectorFloat &to) {
	VectorFloat result(from.size());

	for (unsigned i = 0; i < from.size(); i++) {
		result[i] = to[i] - from[i];
	}

	return result;
}

// ========= //
// OPERATORS //
// ========= //
VectorFloat operator+(VectorFloat a, const VectorFloat &b) {
	for (unsigned i = 0; i < a.size(); i++) {
		a[i] += b[i];
	}

	return a;
}

VectorInt operator+(VectorInt a, const VectorInt &b) {
	for (unsigned i = 0; i < a.size(); i++) {
		a[i] += b[i];
	}

	return a;
}