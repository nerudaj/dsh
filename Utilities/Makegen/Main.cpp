#include <iostream>
#include <fstream>
#include <ciso646>
#include "Makegen.hpp"
#include <Config.hpp>

int main(int argc, char *argv[]) {
	if (argc == 3) {
		if (std::string(argv[1]) == "-i") {
			Makegen::generateMakefile(argv[2]);
			return 0;
		}
	}
	
	Makegen::generateInfile("Makefile.in", Makegen::Mode::Binary);
	return 0;
}