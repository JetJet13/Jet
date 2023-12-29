//
// Created by Johny Georges on 2023-12-23.
//

#include <string>
#include "lexeme.h"
#include "../../shared/utils/to-string/to-string.h"

template <typename T>
Lexeme<T>::Lexeme(std::string name, Token<T>* token) {
    _name = std::move(name);
    _token = token;
}

template <typename T>
Lexeme<T> Lexeme<T>::setName(std::string name) {
    _name = std::move(name);
    return this;
}

template <typename T>
Lexeme<T> Lexeme<T>::setToken(Token<T>* token) {
    _token = token;
    return this;
}

template <typename T>
Lexeme<T> Lexeme<T>::setValue(T value) {
    _token->setValue(value);
    return this;
}

template <typename T>
std::string Lexeme<T>::getName() {
    return _name;
}

template <typename T>
Token<T>* Lexeme<T>::getToken() {
    return _token;
}

template <typename T>
T Lexeme<T>::getValue() {
    return _token->getValue();
}

template <typename T>
std::string Lexeme<T>::toString() {
    std::string lexemeString;
    lexemeString.append(_token->toString());
    lexemeString.append(" | ");
    lexemeString.append("name: ");
    lexemeString.append(_name);
    return lexemeString;
}

// template definitions
template Lexeme<int>::Lexeme(std::string name, Token<int>* token);
template std::string Lexeme<int>::getName();
template Token<int>* Lexeme<int>::getToken();
template int Lexeme<int>::getValue();
template std::string Lexeme<int>::toString();