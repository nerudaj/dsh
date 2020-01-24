#include "Obfuscation.hpp"
#include "Logger.hpp"
#include "ObfuscatedId.hpp"

#include <regex>
#include <string>
#include <unordered_map>

void obfuscateStaticIdentifiers(SourceFile &file) {
    struct Rule {
        std::regex  declaration;
        std::regex  notName;
        std::string prefix;
    };

    std::vector<Rule> rules = {
        { std::regex("\'static\'\\; function [_a-zA-Z][_a-zA-Z0-9]*"), std::regex("\'static\'\\; function "), "f" },
        { std::regex("\'static\'\\; [_a-zA-Z][_a-zA-Z0-9]*\\.prototype\\.[_a-zA-Z][_a-zA-Z0-9]*"), std::regex("\'static\'\\; [_a-zA-Z][_a-zA-Z0-9]*\\.prototype\\."), "p" },
        { std::regex("\'static\'\\; var [_a-zA-Z][_a-zA-Z0-9]*"), std::regex("\'static\'\\; var "), "v" } 
    };

    std::smatch found;
    std::unordered_map<std::string, std::string> ids;

    for (auto rule : rules) {
        std::string filecopy = file.getContent();
        ObfuscatedId obfId(rule.prefix);

        while (std::regex_search(filecopy, found, rule.declaration)) {
            for (auto match : found) {
                std::string identifier = std::regex_replace(std::string(match), rule.notName, "");
                if (ids.find(identifier) != ids.end()) continue;

                ids[identifier] = obfId.read();
                logger.info("static", identifier + " --> " + ids[identifier]);

                obfId.permutate();
            }

            filecopy = found.suffix().str();
        }
    }

    file.replaceStrings(ids);
}

void obfuscateIds(SourceFile &file) {
    std::smatch found;
    std::unordered_map<std::string, std::string> ids;

    std::regex declaration("ID\\(\'[_a-zA-Z0-9]+\'\\)");
    std::string filecopy = file.getContent();
    ObfuscatedId obfId;

    while (std::regex_search(filecopy, found, declaration)) {
        for (auto match : found) {
            std::string raw = std::string(match);
            std::string id = "ID('" + raw.substr(4, raw.size() - 6) + "')";
            if (ids.find(id) != ids.end()) continue;

            ids[id] = "\"" + obfId.read() + "\"";
            logger.info("id", id + " --> " + ids[id]);

            obfId.permutate();
        }

        filecopy = found.suffix().str();
    }

    file.replaceStrings(ids);
    file.replaceString("function ID(id) {return id;}", "");
}

void obfuscateEnums(SourceFile &file) {
    std::smatch found;
    std::unordered_map<std::string, std::string> ids;

    std::regex declaration("ENUM\\(\'[_a-zA-Z0-9]+\'\\)");
    std::string filecopy = file.getContent();
    int idCounter = 0;

    while (std::regex_search(filecopy, found, declaration)) {
        for (auto match : found) {
            std::string raw = std::string(match);
            std::string id = "ENUM('" + raw.substr(6, raw.size() - 8) + "')";
            if (ids.find(id) != ids.end()) continue;

            ids[id] = std::to_string(idCounter);
            logger.info("enum", id + " --> " + ids[id]);

            idCounter++;
        }

        filecopy = found.suffix().str();
    }

    file.replaceStrings(ids);
    file.replaceString("function ENUM(id) {return id;}", "");
}

void obfuscateHinted(const std::vector<std::string> &hints, SourceFile &file) {
    ObfuscatedId obfId("i");
	
	for (auto hint : hints) {
        file.replaceString(hint, obfId.read());
        logger.info("hint", hint + " --> " + obfId.read());
        obfId.permutate();
	}
}