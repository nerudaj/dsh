#pragma once

#include <array>
#include <vector>

#include "Math.hpp"
#include "Convert.hpp"

namespace perlin {
	template<unsigned Dimensions>
	using Vector = std::array<int, Dimensions>;

	enum class GradientComplexity : size_t {
		SlowRadial
	};

	/**
	 *  \brief
	 */
	class RawNoiseGenerator {
	protected:
		std::vector<std::vector<float>> gradients;

		void generateGradients();

		float getValueAt(const std::vector<int> &point) const;
	};

	template<unsigned Dimensions>
	class NoiseGenerator : public RawNoiseGenerator {
	private:
		std::vector<int> gridSize;
		std::vector<int> gridDensity;

		void initialize(const unsigned dimensions) {
			gridSize = {12, 12, 12};
			gridDensity = {3, 3, 3};
			gradients.resize(Math::getDimensionsProduct(gridSize));
			generateGradients();
		}

	public:
		float getValueAt(const Vector<Dimensions> &point) const {
			std::vector<int> templatelessPoint(point.begin(), point.end());
			return getValueAt(templatelessPoint);
		}

		NoiseGenerator() {
			initialize(Dimensions);
		}
	};
}