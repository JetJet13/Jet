//
// Created by Johny Georges on 2023-12-27.
//

#include "token.h"
#include "../../shared/utils/to-string/to-string.h"


Token::Token(Symbol *symbol) {
    _symbol = symbol;
}

Token::Token(Symbol* symbol, int valueId) {
    _symbol = symbol;
    _valueId = valueId;
}

Symbol* Token::getSymbol() {
    return _symbol;
}

SymbolType Token::getSymbolType() {
    return _symbol->getType();
}

std::optional<int> Token::getValueId() {
    return _valueId;
}

Token* Token::setValueId(int valueId) {
    _valueId = valueId;
    return this;
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

bool Token::isEqualTo(Token* otherToken) {
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
