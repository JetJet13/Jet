//
// Created by Johny Georges on 2023-12-24.
//

#ifndef JETLANG_SYMBOL_H
#define JETLANG_SYMBOL_H

#include <string>
#include "types/symbol-type.h"

class Symbol {
protected:
    SymbolType _type;
    std::string _toStringValue;
public:
    Symbol(SymbolType type, std::string toStringValue);
    std::string toString();
};

#endif //JETLANG_SYMBOL_H
