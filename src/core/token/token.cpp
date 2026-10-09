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

#include "token.h"
#include "../../shared/utils/to-string/to-string.h"

Token::Token(std::shared_ptr<Symbol> symbol) {
    _symbol = symbol;
    _rawValue = symbol->toString();
}

Token::Token(std::shared_ptr<Symbol> symbol, std::string rawValue) {
    _symbol = symbol;
    _rawValue = rawValue;
}

Token::Token(std::shared_ptr<Symbol> symbol, std::string rawValue, uint64_t valueId) {
    _symbol = symbol;
    _rawValue = rawValue;
    _valueId = valueId;
}

std::shared_ptr<Symbol> Token::getSymbol() {
    return _symbol;
}

SymbolType Token::getSymbolType() {
    return _symbol->getType();
}

std::string Token::getRawValue() {
    return _rawValue;
}

std::optional<uint64_t> Token::getValueId() {
    return _valueId;
}

std::shared_ptr<Token> Token::setValueId(uint64_t valueId) {
    _valueId = valueId;
    return shared_from_this();
}

std::string Token::toString() {
    std::string tokenString;
    tokenString.append("token: ( ");
    tokenString.append(_symbol->toString());
    if (_valueId) {
        tokenString.append(" | ");
        tokenString.append(" valueId ");
        tokenString.append(ToStringUtil::toString(_valueId.value()));
    }
    tokenString.append(" )");
    return tokenString;
}

bool Token::isEqualTo(std::shared_ptr<Token> otherToken) {
    if (this->getSymbolType() != otherToken->getSymbolType()) {
        return false;
    }

    if (_valueId && !otherToken->getValueId() ||
        !_valueId && otherToken->getValueId() ||
        _valueId.value() != otherToken->getValueId().value()) {
        return false;
    }

    return true;
}
