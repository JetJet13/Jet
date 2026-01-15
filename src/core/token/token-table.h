//
// Created by Johny Georges on 2024-01-09.
//

#ifndef JETLANG_TOKEN_TABLE_H
#define JETLANG_TOKEN_TABLE_H

#include <string>
#include <unordered_map>

class TokenTable {
private:
    std::unordered_map<unsigned long, int> _intMap;
    std::unordered_map<unsigned long, float> _floatMap;
    std::unordered_map<unsigned long, char> _charMap;
    std::unordered_map<unsigned long, std::string> _stringMap;
    std::unordered_map<unsigned long, std::string> _identifierMap;
public:
    TokenTable();
    int getInt(unsigned long key);
    float getFloat(unsigned long key);
    char getChar(unsigned long key);
    std::string getString(unsigned long key);
    std::string getIdentifier(unsigned long key);
    void setInt(unsigned long key, unsigned long value);
    void setFloat(unsigned long key, float value);
    void setChar(unsigned long key, char value);
    void setString(unsigned long key, std::string value);
    void setIdentifier(unsigned long key, std::string value);
};
#endif //JETLANG_TOKEN_TABLE_H
