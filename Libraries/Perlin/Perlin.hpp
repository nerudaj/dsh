#pragma once

#include <array>
#include <vector>

namespace perlin {
	template<unsigned Dimensions>
	using Vector = std::array<int, Dimensions>;
	/**
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
	};*/

	enum class GradientComplexity : size_t {
		SlowRadial
	};

	/**
	 *  \brief
	 */
	template<unsigned Dimensions>
	class NoiseGenerator {
	private:
		std::vector<int> gridSize;
		std::vector<int> gridDensity;
		std::vector<std::vector<float> gradients;

		void generateGradients();
		
		float getValueAt(const std::vector<int> &point) const;

	public:
		float getValueAt(const Vector<Dimensions> &point) const {
			std::vector<int> templatelessPoint(point.begin(), point.end());
			return getValueAt(templatelessPoint);
		}

		NoiseGenerator();
	};
}