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
		std::vector<int> gridSize;
		std::vector<int> gridDensity;
		GradientComplexity complexity;
		unsigned seed;

		void generateGradients(const unsigned dimensions);

		std::vector<float> computeDotProducts(const std::vector<float> &point, int pointIndex) const;

		float getValueAtRaw(const std::vector<int> &point) const;
	};

	template<unsigned Dimensions>
	class NoiseGenerator : public RawNoiseGenerator {
	private:
		void initialize() {
			gridSize = std::vector<int>(Dimensions, 2);
			gridDensity = std::vector<int>(Dimensions, 100);
			gradients.resize(Math::getDimensionsProduct(gridSize));
			seed = 0;
			complexity = GradientComplexity::SlowRadial;
			generateGradients(Dimensions);
		}

	public:
		float getValueAt(const Vector<Dimensions> &point) const {
			std::vector<int> templatelessPoint(point.begin(), point.end());
			return getValueAtRaw(templatelessPoint);
		}

		NoiseGenerator() {
			initialize();
		}
	};
}