#include "Top.hpp"

ParserModule *ParserModule::getModule(const std::string &name) {
    if (name == "MESH") return new ParserModuleMesh();
    if (name == "PLAS") return new ParserModulePlayers();
    return NULL;
}