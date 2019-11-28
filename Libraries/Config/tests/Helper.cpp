#include <fstream>
#include "Helper.hpp"

void Helper::writeFile(const std::string &path, const std::string &blob) {
	std::ofstream save(path);
	save.write(blob.c_str(), blob.size());
	save.close();
	save.clear();
}
