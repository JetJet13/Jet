//
// Created by Johny Georges on 2024-01-09.
//

#include "token-table.h"

TokenTable::TokenTable() {
    _intMap = std::unordered_map<int, int>();
    _floatMap = std::unordered_map<int, float>();
    _charMap = std::unordered_map<int, char>();
    _stringMap = std::unordered_map<int, std::string>();
    _identifierMap = std::unordered_map<int, std::string>();
}


std::optional<int> TokenTable::getInt(int key) {
    auto result = _intMap.find(key);
    if (result == _intMap.end()) {
        return {};
    } else {
        return result->second;
    }
}

std::optional<float> TokenTable::getFloat(int key) {
    auto result = _floatMap.find(key);
    if (result == _floatMap.end()) {
        return {};
    } else {
        return result->second;
    }
}

std::optional<char> TokenTable::getChar(int key) {
    auto result = _charMap.find(key);
    if (result == _charMap.end()) {
        return {};
    } else {
        return result->second;
    }
}

std::optional<std::string> TokenTable::getString(int key) {
    auto result = _stringMap.find(key);
    if (result == _stringMap.end()) {
        return {};
    } else {
        return result->second;
    }
}

std::optional<std::string> TokenTable::getIdentifier(int key) {
    auto result = _identifierMap.find(key);
    if (result == _identifierMap.end()) {
        return {};
    } else {
        return result->second;
    }
}

void TokenTable::setInt(int key, int value) {
    _intMap.insert(std::pair<int, int>(key, value));
}

void TokenTable::setFloat(int key, float value) {
    _floatMap.insert(std::pair<int, float>(key, value));
}

void TokenTable::setChar(int key, char value) {
    _charMap.insert(std::pair<int, char>(key, value));
}

void TokenTable::setString(int key, std::string value) {
    _stringMap.insert(std::pair<int, std::string>(key, value));
}

void TokenTable::setIdentifier(int key, std::string value) {
    _identifierMap.insert(std::pair<int, std::string>(key, value));
}