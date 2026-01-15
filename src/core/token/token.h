//
// Created by Johny Georges on 2023-12-27.
//

#ifndef JETLANG_TOKEN_H
#define JETLANG_TOKEN_H

#include <optional>
#include "../symbol/symbol.h"
#include "../../shared/types/null-type.h"
#include "token-table.h"
#include <memory>

class Token {
private:
    std::shared_ptr<Symbol> _symbol;
    std::optional<unsigned long> _valueId;
    std::string _rawValue;
public:
    explicit Token(std::shared_ptr<Symbol> symbol);
    explicit Token(std::shared_ptr<Symbol> symbol, std::string rawValue);
    Token(std::shared_ptr<Symbol> symbol, std::string rawValue, unsigned long valueId);
    std::shared_ptr<Symbol> getSymbol();
    SymbolType getSymbolType();
    std::string getRawValue();
    std::optional<unsigned long> getValueId();
    Token* setValueId(unsigned long valueId);
    std::string toString();
    bool isEqualTo(Token* otherToken);
};

#endif //JETLANG_TOKEN_H
