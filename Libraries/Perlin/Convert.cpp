#include "Convert.hpp"

using namespace perlin;

VectorFloat Convert::vecIntToOffsetedFloat(const VectorInt &vec, const VectorInt &normalFactor) {
	VectorFloat result(vec.size());

	for (unsigned i = 0; i < vec.size(); i++) {
		// 0.5f offsets coordinate to the middle of the tile
		result[i] = (vec[i] + 0.5f) / normalFactor[i];
	}

	return result;
}