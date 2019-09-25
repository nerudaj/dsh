#pragma once

#include <Test.hpp>
#include "../Perlin.hpp"
#include "../Vector.cpp"

class VectorGetNormalizedIndexZeroTest : public Test {
public:
	void run() override {
		perlin::Vector<3> vec({0, 0, 0});
		int out = vec.getNormalizedIndex({{10, 10, 10}});
		assertEqualStrCompat(out, 0);
	}
	
	std::string name() const override {
		return "VectorGetNormalizedIndexZeroTest";
	}
};

class VectorGetNormalizedIndexOneDimTest : public Test {
private:
	int input;
	int dim;
	int ref;

public:
	void run() override {
		perlin::Vector<1> vec({input});
		int out = vec.getNormalizedIndex({{dim}});
		assertEqualStrCompat(out, ref);
	}
	
	std::string name() const override {
		return "VectorGetNormalizedIndexOneDimTest(" + std::to_string(input) + ")";
	}
	
	VectorGetNormalizedIndexOneDimTest(int input, int dim, int ref) : input(input), dim(dim), ref(ref) {}
};

class VectorGetNormalizedIndexOneDimOverflowTest : public Test {
private:
	int input;
	int dim;
	int ref;

public:
	void run() override {
		perlin::Vector<1> vec({input});
		int out = vec.getNormalizedIndex({{dim}});
		assertEqualStrCompat(out, ref);
	}
	
	std::string name() const override {
		return "VectorGetNormalizedIndexOneDimOverflowTest(" + std::to_string(input) + ")";
	}
	
	VectorGetNormalizedIndexOneDimOverflowTest(int input, int dim, int ref) : input(input), dim(dim), ref(ref) {}
};

template<unsigned Dims>
class VectorGetNormalizedIndexMultiDimTest : public Test {
private:
	perlin::Vector<Dims> in;
	perlin::Vector<Dims> dims;
	int ref;

public:
	void run() override {
		int out = in.getNormalizedIndex(dims);
		assertEqualStrCompat(out, ref);
	}
	
	std::string name() const override {
		return "VectorGetNormalizedIndexMultiDimTest<" + std::to_string(Dims) + ">";
	}
	
	VectorGetNormalizedIndexMultiDimTest(const perlin::Vector<Dims> &in, const perlin::Vector<Dims> &dims, int ref) : in(in), dims(dims), ref(ref) {}
};
