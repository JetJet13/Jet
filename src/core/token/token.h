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
// Created by Johny Georges on 2023-12-27.
//

#ifndef JETLANG_TOKEN_H
#define JETLANG_TOKEN_H

#include <optional>
#include "../symbol/symbol.h"
#include "../../shared/types/null-type.h"
#include "token-table.h"
#include <memory>

class Token : public std::enable_shared_from_this<Token> {
private:
    std::shared_ptr<Symbol> _symbol;
    std::optional<uint64_t> _valueId;
    std::string _rawValue;
public:
    explicit Token(std::shared_ptr<Symbol> symbol);
    explicit Token(std::shared_ptr<Symbol> symbol, std::string rawValue);
    Token(std::shared_ptr<Symbol> symbol, std::string rawValue, uint64_t valueId);
    std::shared_ptr<Symbol> getSymbol();
    SymbolType getSymbolType();
    std::string getRawValue();
    std::optional<uint64_t> getValueId();
    std::shared_ptr<Token> setValueId(uint64_t valueId);
    std::string toString();
    bool isEqualTo(std::shared_ptr<Token> otherToken);
};

#endif //JETLANG_TOKEN_H
