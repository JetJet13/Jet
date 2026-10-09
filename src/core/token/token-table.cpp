// Copyright 2026 Johny Georges
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

//
// Created by Johny Georges on 2024-01-09.
//

#include "token-table.h"

TokenTable::TokenTable() {
    _intMap = std::unordered_map<uint64_t, std::string>();
    _floatMap = std::unordered_map<uint64_t, std::string>();
    _charMap = std::unordered_map<uint64_t, char>();
    _stringMap = std::unordered_map<uint64_t, std::string>();
    _identifierMap = std::unordered_map<uint64_t, std::string>();
}


std::string TokenTable::getInt(uint64_t key) {
    auto result = _intMap.find(key);
    if (result == _intMap.end()) {
        throw std::invalid_argument("no uint64_t value found for key");
    } else {
        return result->second;
    }
}

std::string TokenTable::getFloat(uint64_t key) {
    auto result = _floatMap.find(key);
    if (result == _floatMap.end()) {
        throw std::invalid_argument("no float value found for key");
    } else {
        return result->second;
    }
}

char TokenTable::getChar(uint64_t key) {
    auto result = _charMap.find(key);
    if (result == _charMap.end()) {
        throw std::invalid_argument("no char value found for key");
    } else {
        return result->second;
    }
}

std::string TokenTable::getString(uint64_t key) {
    auto result = _stringMap.find(key);
    if (result == _stringMap.end()) {
        throw std::invalid_argument("no string value found for key");
    } else {
        return result->second;
    }
}

std::string TokenTable::getIdentifier(uint64_t key) {
    auto result = _identifierMap.find(key);
    if (result == _identifierMap.end()) {
        throw std::invalid_argument("no identifier value found for key");
    } else {
        return result->second;
    }
}

void TokenTable::setInt(uint64_t key, std::string value) {
    _intMap.insert(std::pair<uint64_t, std::string>(key, value));
}

void TokenTable::setFloat(uint64_t key, std::string value) {
    _floatMap.insert(std::pair<uint64_t, std::string>(key, value));
}

void TokenTable::setChar(uint64_t key, char value) {
    _charMap.insert(std::pair<uint64_t, char>(key, value));
}

void TokenTable::setString(uint64_t key, std::string value) {
    _stringMap.insert(std::pair<uint64_t, std::string>(key, value));
}

void TokenTable::setIdentifier(uint64_t key, std::string value) {
    _identifierMap.insert(std::pair<uint64_t, std::string>(key, value));
}