#include "Bytestream.hpp"
#include <stdexcept>
#include <iostream>
#include <cstdlib>

#define tostr(x) std::to_string(x)

void assume(bool cond, const std::string &str) {
    if (!cond) throw std::runtime_error(str);
}

class Test {
public:
    virtual void run() =0;

    virtual std::string name() const =0;
};

template<typename T>
class TestUintT : public Test {
protected:
    T ref;

public:
    virtual void run() final override {
        BytestreamOut save("bs");
        save << ref;
        save.close();

        BytestreamIn load("bs");
        T out;
        load >> out;

        system("del bs");

        assume(ref == out, "Value mismatch! Ref = " + tostr(ref) + "; out = " + tostr(out));
    }

    virtual std::string name() const final override {
        return "TestUintT(" + tostr(ref) + ")";
    }

    TestUintT(T value) : ref(value) {}
};

class TestString : public Test {
protected:
    std::string ref;

public:
    virtual void run() final override {
        BytestreamOut save("bs");
        save << ref;
        save.close();

        BytestreamIn load("bs");
        std::string out;
        load >> out;

        //system("del bs");

        assume(ref == out, "Value mismatch! Ref = " + ref + ", out = " + out);
    }

    virtual std::string name() const final override {
        return "TestString(" + ref + ")";
    }

    TestString(std::string input) : ref(input) {}
};

class TestVector16 : public Test {
protected:
    std::vector<uint16_t> ref;

public:
    virtual void run() final override {
        BytestreamOut save("bs");
        save << ref;
        save.close();

        BytestreamIn load("bs");
        std::vector<uint16_t> out;
        load >> out;

        system("del bs");

        assume(ref.size() == out.size(), "Size mismatch! Ref = " + tostr(ref.size()) + "; out = " + tostr(out.size()));
        for (unsigned i = 0; i < ref.size(); i++) {
            assume(ref[i] == out[i], "Value mismatch! i = " + tostr(i) + "; ref = " + tostr(ref[i]) + "; out = " + tostr(out[i]));
        }
    }

    virtual std::string name() const final override {
        return "TestVector16(" + tostr(ref.size()) + ")";
    }

    TestVector16(std::vector<uint16_t> input) : ref(input) {}
};

int main() {
    std::vector<Test*> tests = {
        new TestUintT<uint8_t>(0x00),
        new TestUintT<uint8_t>(0x2A),
        new TestUintT<uint8_t>(0xFF),
        new TestUintT<uint16_t>(0x00),
        new TestUintT<uint16_t>(0x100),
        new TestUintT<uint16_t>(0xFFFF),
        new TestUintT<uint32_t>(0x00),
        new TestUintT<uint32_t>(0x10000),
        new TestUintT<uint32_t>(0xFFFFFFFF),
        new TestUintT<uint64_t>(0x00),
        new TestUintT<uint64_t>(0x100000000),
        new TestUintT<uint64_t>(0xFFFFFFFFFFFFFFFF),
        new TestString(""),
        new TestString("doomista"),
        new TestString("Multi word description of the level."),
        new TestVector16({}),
        new TestVector16({1, 2, 3, 4, 5}),
        new TestVector16({69, 42, 1, 0, 256, 0xffff, 4096})
    };

    std::size_t succ = 0, fail = 0;
    for (auto test : tests) {
        std::cout << "Test: " << test->name() << std::endl;

        try {
            test->run();
            std::cout << "OK\n";
            succ++;
        } catch (std::exception &e) {
            std::cerr << "ERROR: " << e.what() << std::endl;
            fail++;
        }

        delete test;
    }

    std::cout << std::endl;
    std::cout << "SUMMARY:" << std::endl;
    std::cout << "Total  : " << (succ+fail) << std::endl;
    std::cout << "Passed : " << succ << std::endl;
    std::cout << "Failed : " << fail << std::endl;

    return fail;
}