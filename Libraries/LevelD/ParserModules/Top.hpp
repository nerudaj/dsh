#pragma once

#include "../LevelD.hpp"

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
    virtual void parse(const std::vector<uint8_t> &data, LevelD &leveld) const final override;

    virtual std::vector<uint8_t> deparse(const LevelD &leveld) const final override;
};

class ParserModulePlayers : public ParserModule {
public:
    virtual void parse(const std::vector<uint8_t> &data, LevelD &leveld) const final override;

    virtual std::vector<uint8_t> deparse(const LevelD &leveld) const final override;
};