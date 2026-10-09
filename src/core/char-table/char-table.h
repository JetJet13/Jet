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
