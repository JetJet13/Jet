//
// Created by Johny Georges on 2024-01-09.
//

#include "token-table.h"

TokenTable::TokenTable() {
    _intMap = std::unordered_map<unsigned long, std::string>();
    _floatMap = std::unordered_map<unsigned long, std::string>();
    _charMap = std::unordered_map<unsigned long, char>();
    _stringMap = std::unordered_map<unsigned long, std::string>();
    _identifierMap = std::unordered_map<unsigned long, std::string>();
}


std::string TokenTable::getInt(unsigned long key) {
    auto result = _intMap.find(key);
    if (result == _intMap.end()) {
        throw std::invalid_argument("no unsigned long value found for key");
    } else {
        return result->second;
    }
}

std::string TokenTable::getFloat(unsigned long key) {
    auto result = _floatMap.find(key);
    if (result == _floatMap.end()) {
        throw std::invalid_argument("no float value found for key");
    } else {
        return result->second;
    }
}

char TokenTable::getChar(unsigned long key) {
    auto result = _charMap.find(key);
    if (result == _charMap.end()) {
        throw std::invalid_argument("no char value found for key");
    } else {
        return result->second;
    }
}

std::string TokenTable::getString(unsigned long key) {
    auto result = _stringMap.find(key);
    if (result == _stringMap.end()) {
        throw std::invalid_argument("no string value found for key");
    } else {
        return result->second;
    }
}

std::string TokenTable::getIdentifier(unsigned long key) {
    auto result = _identifierMap.find(key);
    if (result == _identifierMap.end()) {
        throw std::invalid_argument("no identifier value found for key");
    } else {
        return result->second;
    }
}

void TokenTable::setInt(unsigned long key, std::string value) {
    _intMap.insert(std::pair<unsigned long, std::string>(key, value));
}

void TokenTable::setFloat(unsigned long key, std::string value) {
    _floatMap.insert(std::pair<unsigned long, std::string>(key, value));
}

void TokenTable::setChar(unsigned long key, char value) {
    _charMap.insert(std::pair<unsigned long, char>(key, value));
}

void TokenTable::setString(unsigned long key, std::string value) {
    _stringMap.insert(std::pair<unsigned long, std::string>(key, value));
}

void TokenTable::setIdentifier(unsigned long key, std::string value) {
    _identifierMap.insert(std::pair<unsigned long, std::string>(key, value));
}