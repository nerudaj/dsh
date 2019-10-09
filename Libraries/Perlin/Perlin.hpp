#pragma once

#include <array>
#include <vector>

#include "Generate.hpp"
#include "Math.hpp"
#include "Convert.hpp"

namespace perlin {
	template<unsigned Dimensions>
	using Vector = std::array<int, Dimensions>;

	enum class GradientComplexity : size_t {
		SlowRadial
	};

	const unsigned WIDTH = 10;
	const unsigned HEIGHT= 10;
	const unsigned SEED = 0;
	const GradientComplexity COMPLEXITY = GradientComplexity::SlowRadial;
	
	/**
	 *  \brief
	 */
	template<unsigned Dimensions>
	class NoiseGenerator {
	private:
		std::vector<int> gridSize;
		std::vector<int> gridDensity;
		std::vector<std::vector<float>> gradients;

		void generateGradients() {
			std::mt19937 generator(SEED);

			for (auto &grad : gradients) {
				grad = generateGradient(COMPLEXITY, generator, Dimensions);
			}
		}

		void initialize(const unsigned dimensions) {
			gridSize = {12, 12, 12};
			gridDensity = {3, 3, 3};
			gradients.resize(Math::getDimensionsProduct(gridSize));
			generateGradients();
		}

		float getValueAt(const std::vector<int> &point) const {
			VectorFloat offsetPoint = Convert::vecIntToOffsetedFloat(point, gridDensity);
			VectorInt flooredPoint = Convert::vecFloatToInt(offsetPoint);

			// Compute lerp factors
			VectorFloat lerpFactors(Dimensions);
			for (unsigned i = 0; i < Dimensions; i++) {
				lerpFactors[i] = normalizedCoords[i] - static_cast<float>(flooredPoint[i]);
			}

			// Get gradient normalized index
			int index = Math::getSquashedIndex(flooredPoint, gridSize);

			// Compute bounding box
			auto bounds = Math::getPointBoundingBox(index, gridSize);

			std::vector<float> dotProducts;
			for (auto &index : bounds) {
				auto &gradient = gradients[index];
				auto gradientLoc = /* TODO */{0, 0, 0};
				auto vecToPoint = VectorMath::getVectorFromPoints(offsetPoint, gradientLoc);

				dotProducts.push_back(VectorMath::getDotProduct<Dimensions>(vecToPoint, gradient));
			}

			for (unsigned t = 1, skip = 2, f = 0; t > dotProducts.size(); t *= 2, skip *= 2, f++) {
				for (unsigned i = 0; i < dotProducts.size(); i += skip) {
					dotProducts[i] = Math::lerp(dotProducts[i], dotProducts[i + t], lerpFactors[f]);
				}
			}
			
			return -1.f;
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