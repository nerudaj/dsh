#include "Waves.hpp"
#include <cmath>
#include <iostream>

const float PI = 3.1415926536f;
const float PIOVER180 = 0.0174532925f;

float power (unsigned base, unsigned exp) {
	float result = 1.f;
	
	for (unsigned i = 0; i < exp; i++) result *= base;
	
	return result;
}

template<class T>
std::vector<T> Waves<T>::square(float frequency, float amplitude, unsigned samples, unsigned samplesPerSecond) {
	std::vector<T> result (samples);
	
	float samplePeriod = samplesPerSecond / frequency; // How many samples per single period
	float maxAmplitude = power(2, sizeof(T) * 8) / 2 - 1; // -1 to prevent off-by-one error
	unsigned halfPeriod = unsigned(samplePeriod / 2);
	
	unsigned cnt = 0, state = -1;
	for (unsigned i = 0; i < samples; i++) {
		result[i] = T(state * maxAmplitude * amplitude + maxAmplitude);
		
		cnt++;
		if (cnt == halfPeriod) {
			state = state == 1 ? -1 : 1;
			cnt = 0;
		}
	}
	
	return result;
}

template<class T>
std::vector<T> Waves<T>::triangle(float frequency, float amplitude, unsigned samples, unsigned samplesPerSecond) {
	std::vector<T> result (samples);
	
	return result;
}

template<class T>
std::vector<T> Waves<T>::sine(float frequency, float amplitude, unsigned samples, unsigned samplesPerSecond) {
	std::vector<T> result (samples);
	
	float samplePeriod = samplesPerSecond / frequency; // How many samples per single period
	float maxAmplitude = power(2, sizeof(T) * 8) / 2 - 1; // -1 to prevent off-by-one error
	
	for (unsigned i = 0; i < samples; i++) {
		// normovana perioda = samplesPerSecond / frekvence
		// 2PI .... normovanaPerioda
		// X  .... sample
		float sample = sin(i * 2 * PI / samplePeriod) * (maxAmplitude * amplitude); 
		result[i] = T(sample + maxAmplitude);
	}
	
	return result;
}

template<class T>
std::vector<T> Waves<T>::sawtooth(float frequency, float amplitude, unsigned samples, unsigned samplesPerSecond) {
	std::vector<T> result (samples);
	
	float samplePeriod = samplesPerSecond / frequency; // How many samples per single period
	float maxAmplitude = power(2, sizeof(T) * 8) - 1; // -1 to prevent off-by-one error
	
	for (unsigned i = 0; i < samples; i++) {
		result[i] = T((i / samplePeriod) * maxAmplitude * amplitude);
	}
	
	return result;
}

template<class T>
std::vector<T> Waves<T>::noise(float frequency, float amplitude, unsigned samples, unsigned samplesPerSecond) {
	std::vector<T> result (samples);
	
	return result;
}