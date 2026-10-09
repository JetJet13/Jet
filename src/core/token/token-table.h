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
