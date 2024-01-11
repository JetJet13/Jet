//
// Created by Johny Georges on 2024-01-09.
//

#ifndef JETLANG_TOKEN_TABLE_H
#define JETLANG_TOKEN_TABLE_H

#include <string>
#include <unordered_map>

class TokenTable {
private:
    std::unordered_map<int, int> _intMap;
    std::unordered_map<int, float> _floatMap;
    std::unordered_map<int, char> _charMap;
    std::unordered_map<int, std::string> _stringMap;
public:
    TokenTable();
    std::optional<int> getInt(int key);
    std::optional<float> getFloat(int key);
    std::optional<char> getChar(int key);
    std::optional<std::string> getString(int key);
    void setInt(int key, int value);
    void setFloat(int key, float value);
    void setChar(int key, char value);
    void setString(int key, std::string value);
};
#endif //JETLANG_TOKEN_TABLE_H
