#pragma once

#include <array>
#include <vector>

#include "Math.hpp"
#include "Convert.hpp"

namespace perlin {
	template<unsigned Dimensions>
	using Vector = std::array<int, Dimensions>;

	enum class GradientComplexity : size_t {
		SlowRadial,
		FastOrthogonal
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
		void reinit() {
			gradients.resize(Math::getDimensionsProduct(gridSize));
			generateGradients(Dimensions);
		}

		void init() {
			gridSize = std::vector<int>(Dimensions, 2);
			gridDensity = std::vector<int>(Dimensions, 100);
			seed = 0;
			complexity = GradientComplexity::FastOrthogonal;
			reinit();
		}

	public:
		float getValueAt(const Vector<Dimensions> &point) const {
			std::vector<int> templatelessPoint(point.begin(), point.end());
			return getValueAtRaw(templatelessPoint);
		}

		void setGradientGridSize(const Vector<Dimensions> &size) {
			gridSize = std::vector<int>(size.begin(), size.end());
			
			for (auto &dim : gridSize) dim++;

			reinit();
		}

		void setGradientGridDensity(const Vector<Dimensions> &density) {
			gridDensity = std::vector<int>(density.begin(), density.end());
			reinit();
		}

		NoiseGenerator() {
			init();
		}
	};
}