#pragma once

#include <array>
#include <vector>
#include <memory>

namespace perlin {
	/**
	 *  \brief
	 */
	template<unsigned Dimensions>
	class Vector {
	private:
		std::array<int, Dimensions> data;

	public:
		int getNormalizedIndex(const Vector<Dimensions> &dims) const;

		Vector(const std::array<int, Dimensions> &dims) : data(dims) {}
	};

	enum class GradientComplexity : size_t {
		SlowRadial
	};

	/**
	 *  \brief
	 */
	template<unsigned Dimensions>
	using Gradient = std::array<float, Dimensions>;

	/**
	 *  \brief
	 */
	template<unsigned Dimensions>
	using GradientVector = std::vector<Gradient<Dimensions>>;

	/**
	 *  \brief
	 */
	template<unsigned Dimensions>
	class NoiseGenerator {
	private:
		GradientVector<Dimensions> gradients;

	public:
		float getValueAt(const perlin::Vector<Dimensions> &coords) const;
	};

	typedef NoiseGenerator<1> NoiseGenerator1D;
	typedef NoiseGenerator<2> NoiseGenerator2D;
	typedef NoiseGenerator<3> NoiseGenerator3D;
	typedef NoiseGenerator<4> NoiseGenerator4D;
	typedef NoiseGenerator<5> NoiseGenerator5D;
}