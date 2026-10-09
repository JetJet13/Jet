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
// Created by Johny Georges on 2023-12-23.
//

#include <string>
#include "lexeme.h"
#include "../../shared/utils/to-string/to-string.h"
#include "../../shared/utils/logger/logger.h"

Lexeme::Lexeme(std::shared_ptr<Token> token) {
    _token = token;
    _startPosition = std::make_shared<Position>();
    _endPosition = std::make_shared<Position>();
}

Lexeme::Lexeme(std::shared_ptr<Token> token, uint64_t startLine, uint64_t startColumn, uint64_t endLine, uint64_t endColumn) {
    _token = token;
    _startPosition = std::make_shared<Position>(startLine, startColumn);
    _endPosition = std::make_shared<Position>(endLine, endColumn);
}

std::shared_ptr<Token> Lexeme::getToken() {
    return _token;
}

std::shared_ptr<Position> Lexeme::getStartPosition() {
    return _startPosition;
}

std::shared_ptr<Position> Lexeme::getEndPosition() {
    return _endPosition;
}

std::string Lexeme::toString() {
    std::string lexemeString;
    lexemeString.append(_token->toString());
    lexemeString.append(" | ");
    lexemeString.append("line: ");
    lexemeString.append(ToStringUtil::toString(_startPosition->getLine()));
    lexemeString.append(" | ");
    lexemeString.append("column: ");
    lexemeString.append(ToStringUtil::toString(_startPosition->getColumn()));
    return lexemeString;
}

bool Lexeme::hasSameSymbolTypeAs(std::shared_ptr<Lexeme> other) {
    auto result = this->getToken()->getSymbolType() == other->getToken()->getSymbolType();
    return result;
}

bool Lexeme::isEqualTo(std::shared_ptr<Lexeme> other) {
    return this->getToken()->isEqualTo(other->getToken());
}