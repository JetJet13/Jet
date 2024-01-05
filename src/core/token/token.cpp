//
// Created by Johny Georges on 2023-12-27.
//

#include "token.h"
#include "../../shared/utils/to-string/to-string.h"


Token::Token(Symbol *symbol) {
    _symbol = symbol;
}

void Token::setValueId(int valueId) {
    _valueId = valueId;
}

std::optional<int> Token::getValueId() {
    return _valueId;
}

std::string Token::toString() {
    std::string tokenString;
    tokenString.append("token: (");
    tokenString.append(_symbol->toString());
    tokenString.append(" | ");
    tokenString.append(" valueId ");
    tokenString.append(ToStringUtil::toString(_valueId));
    tokenString.append(")");
    return tokenString;
}
