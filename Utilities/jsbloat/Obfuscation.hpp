#pragma once

#include <vector>
#include <string>
#include "SourceFile.hpp"

void obfuscateStaticIdentifiers(SourceFile &file);

void obfuscateIds(SourceFile &file);

void obfuscateEnums(SourceFile &file);

void obfuscateHinted(const std::vector<std::string> &hints, SourceFile &file);