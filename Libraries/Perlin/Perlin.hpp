#pragma once

#include <array>
#include <vector>

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

		int getDim(unsigned dim) const {
			return data.at(dim);
		}

		int getDimsProduct() const;

		void normalizeDims(const Vector<Dimensions> &other);

		Vector(const std::array<int, Dimensions> &dims) : data(dims) {}
		Vector(int coord) : data(std::array<int, Dimensions>()) {
			data.fill(coord);
		}
	};

	enum class GradientComplexity : size_t {
		SlowRadial
	};

	/**
	 *  \brief
	 */
	template<unsigned Dimensions>
	using Gradient = std::array<float, Dimensions>;

	// TRUE VECTOR MATH
	template<typename T, unsigned Dimensions>
	using VVector = std::array<T, Dimensions>;
	
	template<unsigned Dimensions>
	using IntVector = VVector<int, Dimensions>;

	template<unsigned Dimensions>
	using FloatVector = VVector<float, Dimensions>;

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
		Vector<Dimensions> gridSize;
		Vector<Dimensions> gridDensity; // How many tiles fit between two gradients
		std::vector<FloatVector<Dimensions>> gradients;

		void generateGradients();

	public:
		float getValueAt(perlin::Vector<Dimensions> coords) const;

		NoiseGenerator();
	};

	typedef NoiseGenerator<1> NoiseGenerator1D;
	typedef NoiseGenerator<2> NoiseGenerator2D;
	typedef NoiseGenerator<3> NoiseGenerator3D;
	typedef NoiseGenerator<4> NoiseGenerator4D;
	typedef NoiseGenerator<5> NoiseGenerator5D;
}