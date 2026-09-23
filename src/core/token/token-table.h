//
// Created by Johny Georges on 2024-01-09.
//

#ifndef JETLANG_TOKEN_TABLE_H
#define JETLANG_TOKEN_TABLE_H

#include <string>
#include <unordered_map>

class TokenTable {
private:
    std::unordered_map<uint64_t, std::string> _intMap;
    std::unordered_map<uint64_t, std::string> _floatMap;
    std::unordered_map<uint64_t, char> _charMap;
    std::unordered_map<uint64_t, std::string> _stringMap;
    std::unordered_map<uint64_t, std::string> _identifierMap;
public:
    TokenTable();
    std::string getInt(uint64_t key);
    std::string getFloat(uint64_t key);
    char getChar(uint64_t key);
    std::string getString(uint64_t key);
    std::string getIdentifier(uint64_t key);
    void setInt(uint64_t key, std::string value);
    void setFloat(uint64_t key, std::string value);
    void setChar(uint64_t key, char value);
    void setString(uint64_t key, std::string value);
    void setIdentifier(uint64_t key, std::string value);
};
#endif //JETLANG_TOKEN_TABLE_H
