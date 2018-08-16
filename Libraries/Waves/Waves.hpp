#ifndef WAVES_HPP_
#define WAVES_HPP_

#include <vector>
#include <cstdint>

template<class T>
class Waves {
public:
	static std::vector<T> square(float frequency, float amplitude, unsigned samples, unsigned samplesPerSecond);
	
	static std::vector<T> triangle(float frequency, float amplitude, unsigned samples, unsigned samplesPerSecond);
	
	static std::vector<T> sine(float frequency, float amplitude, unsigned samples, unsigned samplesPerSecond);
	
	static std::vector<T> sawtooth(float frequency, float amplitude, unsigned samples, unsigned samplesPerSecond);
	
	static std::vector<T> noise(float frequency, float amplitude, unsigned samples, unsigned samplesPerSecond);
};

// Instantiate templates
template class Waves<uint8_t>;
template class Waves<uint16_t>;
template class Waves<uint32_t>;

// And alias them
typedef Waves<uint8_t>  Waves8;
typedef Waves<uint16_t> Waves16;
typedef Waves<uint32_t> Waves32;

#endif
