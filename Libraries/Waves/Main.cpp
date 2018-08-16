#include <iostream>
#include "Waves.hpp"

int main() {
	auto samples = Waves16::sawtooth(10.f, 1.f, 400, 200);
	
	for (unsigned i = 0; i < samples.size(); i++) {
		std::cout << i << "," << samples[i] << "\n";
	}
	
	return 0;
}