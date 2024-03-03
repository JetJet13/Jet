//
// Created by Johny Georges on 2023-12-23.
//

#include <string>
#include "lexeme.h"
#include "../../shared/utils/to-string/to-string.h"
#include "../../shared/utils/logger/logger.h"

Lexeme::Lexeme(Token* token, uint8_t line, uint8_t startPosition) {
    _token = token;
    _line = line;
    _start_position = startPosition;
}

Token* Lexeme::getToken() {
    return _token;
}

int Lexeme::getLine() const {
    return _line;
}

int Lexeme::getPosition() const {
    return _start_position;
}

std::string Lexeme::toString() {
    std::string lexemeString;
    lexemeString.append(_token->toString());
    lexemeString.append(" | ");
    lexemeString.append("line: ");
    lexemeString.append(ToStringUtil::toString(_line));
    lexemeString.append(" | ");
    lexemeString.append("position: ");
    lexemeString.append(ToStringUtil::toString(_start_position));
    return lexemeString;
}

bool Lexeme::hasSameSymbolTypeAs(Lexeme* other) {
    auto result = this->getToken()->getSymbolType() == other->getToken()->getSymbolType();
    return result;
}