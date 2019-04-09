#pragma once

#include "../LevelD.hpp"
#include <stdexcept>

const std::string TMP_LVD_FILE = "tmp.lvd";

#define tostr(x) std::to_string(x)

void assume(bool cond, const std::string &str);

class Test {
public:
    virtual void run() =0;

    virtual std::string name() const =0;
};

class TestMetadata : public Test {
protected:
    LevelD ref;

public:
    virtual void run() final override;
    virtual std::string name() const final override { return "TestMetadata"; }
    TestMetadata(const LevelD &ref) : ref(ref) {}
};

class TestMesh : public Test {
protected:
    LevelD ref;

public:
    virtual void run() final override;
    virtual std::string name() const final override { return "TestMesh"; }
    TestMesh(const LevelD &ref) : ref(ref) {}
};