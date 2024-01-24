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

bool Symbol::isMalformed() {
    return _type == SYM_MALFORMED;
}

bool Symbol::isBang() {
    return _type == SYM_BANG;
}

bool Symbol::isEqual() {
    return _type == SYM_EQUAL;
}

bool Symbol::isInt() {
    return _type == SYM_INT;
}

bool Symbol::isFloat() {
    return _type == SYM_FLOAT;
}

bool Symbol::isChar() {
    return _type == SYM_CHAR;
}

bool Symbol::isLet() {
    return _type == SYM_LET;
}

bool Symbol::isConst() {
    return _type == SYM_CONST;
}

bool Symbol::isString() {
    return _type == SYM_STRING;
}

bool Symbol::isIdentifier() {
    return _type == SYM_IDENTIFIER;
}

SymbolType Symbol::getType() {
    return _type;
}

std::string Symbol::toString() {
    return _toStringValue;
}