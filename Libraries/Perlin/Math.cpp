#include "Math.hpp"

using namespace perlin;

unsigned Math::getDimensionsProduct(const VectorInt &vec) {
	unsigned result = 1;

	for (auto &v : vec) result *= v;

	return result;
}

int Math::getSquashedIndex(const VectorInt &source, const VectorInt &limits) {
	int result = 0;

	for (unsigned i = 0; i < source.size(); i++) {
		int normalizedDataI = source[i] % limits[i];
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
		unsigned limit = result.size();
		unsigned offset = 1;

		for (unsigned p = 0, j = i - 1; p < i; p++, j--) {
			offset *= limits[j];
		}

		for (unsigned p = 0; p < limit; p++) {
			result.push_back(result[p] + offset);
		}
	}

	return result;
}