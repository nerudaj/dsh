#include <Test.hpp>

#include "VectorTests.hpp"

int main() {
	Testrunner runner({
		new VectorGetNormalizedIndexZeroTest(),
		new VectorGetNormalizedIndexOneDimTest(2, 10, 2),
		new VectorGetNormalizedIndexOneDimOverflowTest(2, 1, 0),
		new VectorGetNormalizedIndexOneDimOverflowTest(10, 7, 3),
		new VectorGetNormalizedIndexMultiDimTest<2>({{1, 1}}, {{2, 2}}, 3),
		new VectorGetNormalizedIndexMultiDimTest<2>({{5, 1}}, {{10, 10}}, 15),
		new VectorGetNormalizedIndexMultiDimTest<2>({{5, 1}}, {{1, 1}}, 0),
		new VectorGetNormalizedIndexMultiDimTest<3>({{1, 1, 1}}, {{2, 2, 2}}, 7),
		new VectorGetNormalizedIndexMultiDimTest<4>({{1, 1, 1, 1}}, {{2, 2, 2, 2}}, 15)
	});
	
	return runner.evaluateTestcases(true);
}