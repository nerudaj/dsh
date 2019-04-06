#include "Top.hpp"

ParserModule *ParserModule::getModule(const std::string &name) {
    if (name == "MESH") return new ParserModuleMesh();
    else if (name == "PLAS") return new ParserModulePlayers();
    else if (name == "META") return new ParserModuleMetadata();
    return NULL;
}