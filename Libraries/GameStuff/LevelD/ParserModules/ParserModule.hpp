#pragma once

#include "../LevelDHandler.hpp"

#include <vector>
#include <string>

class ParserModule {
public:
    static ParserModule *getModule(const std::string &name);

    virtual void parse(const std::vector<uint8_t> &data, LevelD &leveld) const = 0;

    virtual std::vector<uint8_t> deparse(const LevelD &leveld) const = 0;
};

class ParserModuleMesh : public ParserModule {
public:
    void parse(const std::vector<uint8_t> &data, LevelD &leveld) const;

    std::vector<uint8_t> deparse(const LevelD &leveld) const;
};

ParserModule *ParserModule::getModule(const std::string &name) {
    if (name == "MESH") return new ParserModuleMesh();
    return NULL;
}