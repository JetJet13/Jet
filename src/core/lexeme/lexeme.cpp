//
// Created by Johny Georges on 2023-12-23.
//

#include <string>
#include "lexeme.h"
#include "../../shared/utils/to-string/to-string.h"

template <typename TValue>
Lexeme<TValue>::Lexeme(std::string name, Symbol* symbol, TValue value) {
    _name = std::move(name);
    _symbol = symbol;
    _value = value;
}

template <typename TValue>
Lexeme<TValue> Lexeme<TValue>::setName(std::string name) {
    _name = std::move(name);
    return this;
}

template <typename TValue>
Lexeme<TValue> Lexeme<TValue>::setSymbol(Symbol* symbol) {
    _symbol = symbol;
    return this;
}

template <typename TValue>
Lexeme<TValue> Lexeme<TValue>::setValue(TValue value) {
    _value = value;
    return this;
}

template <typename TValue>
std::string Lexeme<TValue>::getName() {
    return _name;
}

template <typename TValue>
Symbol* Lexeme<TValue>::getSymbol() {
    return _symbol;
}

template <typename TValue>
TValue Lexeme<TValue>::getValue() {
    return _value;
}

template <typename TValue>
std::string Lexeme<TValue>::toString() {
    std::string lexemeString;
    lexemeString.append("symbol: ");
    lexemeString.append(_symbol->toString());
    lexemeString.append(" | ");
    lexemeString.append("name: ");
    lexemeString.append(_name);
    lexemeString.append(" | ");
    lexemeString.append("value: ");
    lexemeString.append(ToStringUtil::toString(_value));
    return lexemeString;
}

// template definitions
template Lexeme<int>::Lexeme(std::string name, Symbol* symbol, int value);
template std::string Lexeme<int>::getName();
template Symbol* Lexeme<int>::getSymbol();
template int Lexeme<int>::getValue();
template std::string Lexeme<int>::toString();