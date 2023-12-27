//
// Created by Johny Georges on 2023-12-23.
//

#ifndef JETLANG_LEXEME_H
#define JETLANG_LEXEME_H

#include <string>
#include "../symbol/symbol.h"

template <typename TValue>
class Lexeme {
private:
    std::string _name;
    Symbol* _symbol;
    TValue _value;
public:
    Lexeme(std::string name, Symbol* symbol, TValue value);
    Lexeme<TValue> setName(std::string name);
    Lexeme<TValue> setSymbol(Symbol* symbol);
    Lexeme<TValue> setValue(TValue value);
    std::string getName();
    Symbol* getSymbol();
    TValue getValue();
    std::string toString();
};

#endif //JETLANG_LEXEME_H
