//
// Created by Johny Georges on 2023-12-23.
//

#ifndef JETLANG_LEXEME_H
#define JETLANG_LEXEME_H

#include <string>
#include "../symbol/symbol.h"
#include "../token/token.h"

template <typename T>
class Lexeme {
private:
    std::string _name;
    Token<T>* _token;
public:
    Lexeme(std::string name, Token<T>* token);
    Lexeme<T> setName(std::string name);
    Lexeme<T> setToken(Token<T>* token);
    Lexeme<T> setValue(T value);
    std::string getName();
    Token<T>* getToken();
    T getValue();
    std::string toString();
};

#endif //JETLANG_LEXEME_H
