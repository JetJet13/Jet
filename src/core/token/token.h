//
// Created by Johny Georges on 2023-12-27.
//

#ifndef JETLANG_TOKEN_H
#define JETLANG_TOKEN_H

#include <optional>
#include "../symbol/symbol.h"
#include "../../shared/types/null-type.h"
#include "token-table.h"

class Token {
private:
    Symbol* _symbol;
    std::optional<int> _valueId;
    std::string _rawValue;
public:
    explicit Token(Symbol* symbol);
    explicit Token(Symbol* symbol, std::string rawValue);
    Token(Symbol* symbol, std::string rawValue, int valueId);
    Symbol* getSymbol();
    SymbolType getSymbolType();
    std::string getRawValue();
    std::optional<int> getValueId();
    Token* setValueId(int valueId);
    std::string toString();
    bool isEqualTo(Token* otherToken);
};

#endif //JETLANG_TOKEN_H
