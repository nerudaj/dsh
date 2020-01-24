#pragma once

#include <string>
#include <vector>
#include "SourceFile.hpp"

namespace io {
    SourceFile concatenateSourceFiles(const std::vector<std::string> &filenames);

    std::vector<std::string> loadHintFile(const std::string &filename);
}