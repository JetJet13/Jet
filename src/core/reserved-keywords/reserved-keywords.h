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
// Created by Johny Georges on 2023-12-29.
//

#ifndef JETLANG_RESERVED_KEYWORDS_H
#define JETLANG_RESERVED_KEYWORDS_H

#include <string>
#include <vector>
#include <unordered_map>
#include "../symbol/symbol.h"

class ReservedKeywords {
private:
    std::unordered_map<std::string, std::shared_ptr<Symbol>> _keywordMap;
    std::vector<std::shared_ptr<Symbol>> _keywordSymbols;
    void init();
    void initKeywordSymbolList();
    void add(const std::string& keyword, std::shared_ptr<Symbol> symbol);
public:
    ReservedKeywords();
    std::optional<std::shared_ptr<Symbol>> match(const std::string& matchTerm);
    std::optional<std::shared_ptr<Symbol>> match(std::optional<char> matchChar);
    bool isKeywordSymbol(std::shared_ptr<Symbol> symbol);
};
#endif //JETLANG_RESERVED_KEYWORDS_H
