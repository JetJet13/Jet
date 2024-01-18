//
// Created by Johny Georges on 2024-01-10.
//

#ifndef JETLANG_CHAR_TABLE_H
#define JETLANG_CHAR_TABLE_H

#include <string>
#include <unordered_map>

class CharTable {
private:
    std::unordered_map<std::string, char> _charMap;
    void init();
    void add(const std::string& keyword, char symbol);
public:
    CharTable();
    std::optional<char> match(const std::string& matchTerm);
    std::optional<char> match(std::optional<char> matchChar);
};
#endif //JETLANG_CHAR_TABLE_H
