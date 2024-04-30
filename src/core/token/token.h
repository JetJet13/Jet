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
public:
    explicit Token(Symbol* symbol);
    Token(Symbol* symbol, int valueId);
    Symbol* getSymbol();
    SymbolType getSymbolType();
    std::optional<int> getValueId();
    Token* setValueId(int valueId);
    std::string toString();
    bool isEqualTo(Token* otherToken);
};

#endif //JETLANG_TOKEN_H
