#include "Conversions.hpp"

using namespace perlin;

VectorInt Convert::vecFloatToInt(const VectorFloat &vec) {
	return VectorInt(vec.begin(), vec.end());
}

VectorFloat Convert::vecIntToFloat(const VectorInt &vec) {
	return VectorFloat(vec.begin(), vec.end());
}