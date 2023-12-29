//
// Created by Johny Georges on 2023-12-27.
//

#ifndef JETLANG_TOKEN_H
#define JETLANG_TOKEN_H

#include "../symbol/symbol.h"

template <typename T = void>
class Token {
private:
    Symbol* _symbol;
    T _value;
public:
    Token(Symbol* symbol, T value);
    explicit Token(Symbol* symbol);
    void setValue(T value);
    T getValue();
    std::string toString();
};

#endif //JETLANG_TOKEN_H
