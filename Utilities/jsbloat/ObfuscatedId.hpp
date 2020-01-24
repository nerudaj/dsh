#pragma once

class ObfuscatedId {
private:
    std::string id = "a";
    std::string prefix = "";

public:
    std::string read() const {
        return prefix + id;
    }

    void permutate() {
        const std::string IDCODES = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVXYZ012345678_";

        auto last = id.size() - 1;
        auto loc = IDCODES.find(id[last]);

        if (IDCODES[loc] == '_') {
            id += IDCODES[0];
        } else id[last] = IDCODES[++loc];
    }

    ObfuscatedId() {}
    ObfuscatedId(const std::string &prefix) : prefix(prefix) {}
};