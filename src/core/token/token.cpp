//
// Created by Johny Georges on 2023-12-27.
//

#include "token.h"
#include "../../shared/utils/to-string/to-string.h"
#include "../../shared/types/null-type.h"

template <typename T>
Token<T>::Token(Symbol *symbol, T value) {
    _symbol = symbol;
    _value = value;
}

template <typename T>
Token<T>::Token(Symbol *symbol) {
    _symbol = symbol;
}

template <typename T>
void Token<T>::setValue(T value) {
    _value = value;
}

template <typename T>
T Token<T>::getValue() {
    return _value;
}

template <typename T>
std::string Token<T>::toString() {
    std::string tokenString;
    tokenString.append("token: (");
    tokenString.append(_symbol->toString());
    tokenString.append(" | ");
    tokenString.append(ToStringUtil::toString(_value));
    tokenString.append(")");
    return tokenString;
}

template Token<int>::Token(Symbol *symbol, int value);
template Token<NullType>::Token(Symbol *symbol);
template int Token<int>::getValue();
template std::string Token<int>::toString();
