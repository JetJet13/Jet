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

Token::Token(std::shared_ptr<Symbol> symbol, std::string rawValue, unsigned long valueId) {
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

std::optional<unsigned long> Token::getValueId() {
    return _valueId;
}

Token* Token::setValueId(unsigned long valueId) {
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
