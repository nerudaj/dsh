#pragma once

#include <string>
#include <unordered_map>

class SourceFile {
private:
    std::string content = "";

public:
    const std::string &getContent() const {
        return content;
    }

    /**
     *  Replaces key of \p strings with its value
     */
    void replaceStrings(const std::unordered_map<std::string, std::string> &strings);

    void replaceString(const std::string &from, const std::string &to);

    void loadFromFile(const std::string &filename);

    void saveToFile(const std::string &filename);

    void concatenate(const SourceFile &other);
};