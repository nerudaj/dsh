#include "Math.hpp"
#include <cassert>

using namespace perlin;

unsigned Math::getDimensionsProduct(const VectorInt &vec) {
	unsigned result = 1;

	for (auto &v : vec) result *= v;

	return result;
}

int Math::getSquashedIndex(const VectorInt &source, const VectorInt &limits) {
	int result = 0;

	for (unsigned i = 0; i < source.size(); i++) {
		int normalizedDataI = source[i] % (limits[i] - 1);
		int dataMultiplicator = 1;

		for (unsigned p = 0, j = i - 1; p < i; p++, j--) {
			dataMultiplicator *= limits[j];
		}

		result += normalizedDataI * dataMultiplicator;
	}

	return result;
}

std::vector<int> Math::getPointBoundingBox(int start, const VectorInt &limits) {
	std::vector<int> result = { start, start + 1 };

	for (unsigned i = 1; i < limits.size(); i++) {
		unsigned offset = 1;

		for (unsigned p = 0, j = i - 1; p < i; p++, j--) {
			offset *= limits[j];
		}

		unsigned limit = result.size();
		for (unsigned p = 0; p < limit; p++) {
			result.push_back(result[p] + offset);
		}
	}

	return result;
}

VectorFloat Math::computeLerpFactors(const VectorInt &origin, const VectorFloat &target) {
	assert(origin.size() == target.size());

	VectorFloat lerpFactors(origin.size());

	for (unsigned i = 0; i < origin.size(); i++) {
		lerpFactors[i] = target[i] - static_cast<float>(origin[i]);
	}

	return lerpFactors;
}

VectorFloat Math::vectorFromIndex(int index, const VectorInt &gridSize) {
	VectorFloat result(gridSize.size());

	unsigned multiplier = 1;
	for (unsigned i = 0; i < gridSize.size(); i++) {
		result[i] = index % (multiplier * gridSize[i]) / multiplier;
		multiplier *= gridSize[i];
	}

	return result;
}

float Math::reduceDotProducts(VectorFloat dotProducts, const VectorFloat &lerpFactors) {
	for (unsigned t = 1, skip = 2, f = 0; t < dotProducts.size(); t *= 2, skip *= 2, f++) {
		for (unsigned i = 0; i < dotProducts.size(); i += skip) {
			dotProducts[i] = Math::lerp(dotProducts[i], dotProducts[i + t], lerpFactors[f]);
		}
	}

	return dotProducts[0];
}