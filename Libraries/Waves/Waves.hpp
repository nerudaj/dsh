#ifndef WAVES_HPP_
#define WAVES_HPP_

#include <vector>
#include <cstdint>

template<class T>
/**
 *  \brief Set of simple functions for generating sound waves
 *  
 *  \details Each method generates waves with unsigned int samples at selectable bit width. Use \ref Waves8, \ref Waves16 and \ref Waves32
 *  to generate 8bit, 16bit or 32bit samples.
 */
class Waves {
public:
	/**
	 *  \brief Generate a square wave
	 *  
	 *  \param [in] frequency How many times the wave will repeat in single second
	 *  \param [in] amplitude How loud the wave will be (Number from 0 to 1)
	 *  \param [in] samples How many samples to generate
	 *  \param [in] samplesPerSecond How many samples will be in second
	 *  \return Vector of samples. Might throw exception if it runs out of memory
	 *  
	 *  \details Square wave have samples alternating between -amplitute to +amplitude
	 */
	static std::vector<T> square(float frequency, float amplitude, unsigned samples, unsigned samplesPerSecond);
	
	/**
	 *  \brief Generate a triangle wave
	 *  
	 *  \param [in] frequency How many times the wave will repeat in single second
	 *  \param [in] amplitude How loud the wave will be (Number from 0 to 1)
	 *  \param [in] samples How many samples to generate
	 *  \param [in] samplesPerSecond How many samples will be in second
	 *  \return Vector of samples. Might throw exception if it runs out of memory
	 *  
	 *  \details Triangle wave has the same behaviour as a sine wave, only with linear progression. It starts in 0,
	 *  goes to +amplitude, then to -amplitude and then back to 0.
	 */
	static std::vector<T> triangle(float frequency, float amplitude, unsigned samples, unsigned samplesPerSecond);
	
	/**
	 *  \brief Generate a sine wave
	 *  
	 *  \param [in] frequency How many times the wave will repeat in single second
	 *  \param [in] amplitude How loud the wave will be (Number from 0 to 1)
	 *  \param [in] samples How many samples to generate
	 *  \param [in] samplesPerSecond How many samples will be in second
	 *  \return Vector of samples. Might throw exception if it runs out of memory
	 *  
	 *  \details Simple sine wave
	 */
	static std::vector<T> sine(float frequency, float amplitude, unsigned samples, unsigned samplesPerSecond);
	
	/**
	 *  \brief Generate a sawtooth wave
	 *  
	 *  \param [in] frequency How many times the wave will repeat in single second
	 *  \param [in] amplitude How loud the wave will be (Number from 0 to 1)
	 *  \param [in] samples How many samples to generate
	 *  \param [in] samplesPerSecond How many samples will be in second
	 *  \return Vector of samples. Might throw exception if it runs out of memory
	 *  
	 *  \details Sawtooth wave goes linearly from -amplitude to +amplitude and then, in a single sample, falls
	 *  back to -amplitude
	 */
	static std::vector<T> sawtooth(float frequency, float amplitude, unsigned samples, unsigned samplesPerSecond);
	
	/**
	 *  \brief Generate a simple random noise
	 *  
	 *  \param [in] amplitude How loud the wave will be (Number from 0 to 1)
	 *  \param [in] samples How many samples to generate
	 *  \return Vector of samples. Might throw exception if it runs out of memory
	 */
	static std::vector<T> noise(float amplitude, unsigned samples);
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
