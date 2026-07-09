//
// Created by Johny Georges on 2023-12-23.
//

#include <string>
#include "lexeme.h"
#include "../../shared/utils/to-string/to-string.h"
#include "../../shared/utils/logger/logger.h"

Lexeme::Lexeme(Token* token) {
    _token = token;
    _startPosition = std::make_shared<Position>();
    _endPosition = std::make_shared<Position>();
}

Lexeme::Lexeme(Token* token, unsigned long startLine, unsigned long startColumn, unsigned long endLine, unsigned long endColumn) {
    _token = token;
    _startPosition = std::make_shared<Position>(startLine, startColumn);
    _endPosition = std::make_shared<Position>(endLine, endColumn);
}

Token* Lexeme::getToken() {
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

bool Lexeme::hasSameSymbolTypeAs(Lexeme* other) {
    auto result = this->getToken()->getSymbolType() == other->getToken()->getSymbolType();
    return result;
}

bool Lexeme::isEqualTo(Lexeme* other) {
    return this->getToken()->isEqualTo(other->getToken());
}