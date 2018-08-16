#ifndef MAKEGEN_HPP_
#define MAKEGEN_HPP_

#include <iostream>

class Makegen {
public:
	enum Mode {
		Library, Binary
	};

	static bool generateMakefile(const std::string &infile, const std::string &outfile);
	
	static bool generateInfile(const std::string &filename, Makegen::Mode mode);
};

#endif
