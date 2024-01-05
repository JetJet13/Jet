//
// Created by Johny Georges on 2023-12-24.
//

#include "symbol.h"
#include "types/symbol-type.h"
#include <utility>

Symbol::Symbol(SymbolType type, std::string toStringValue) {
    _type = type;
    _toStringValue = std::move(toStringValue);
}

bool Symbol::isSemicolon() {
    return _type == SYM_SEMICOLON;
}

std::string Symbol::toString() {
    return _toStringValue;
}