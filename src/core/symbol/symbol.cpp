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

bool Symbol::isComma() {
    return _type == SYM_COMMA;
}

bool Symbol::isColon() {
    return _type == SYM_COLON;
}

bool Symbol::isPeriod() {
    return _type == SYM_PERIOD;
}

bool Symbol::isLeftBracket() {
    return _type == SYM_LEFT_BRACKET;
}

bool Symbol::isRightBracket() {
    return _type == SYM_RIGHT_BRACKET;
}

bool Symbol::isLeftBrace() {
    return _type == SYM_LEFT_BRACE;
}

bool Symbol::isRightBrace() {
    return _type == SYM_RIGHT_BRACE;
}

bool Symbol::isLeftParentheses() {
    return _type == SYM_LEFT_PAREN;
}

bool Symbol::isRightParentheses() {
    return _type == SYM_RIGHT_PAREN;
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

bool Symbol::isVarTypeQualifier() {
    return this->isLet() || this->isConst();
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

bool Symbol::isBoolean() {
    return _type == SYM_TRUE || _type == SYM_FALSE;
}

bool Symbol::isPlus() {
    return _type == SYM_PLUS;
}

bool Symbol::isMinus() {
    return _type == SYM_MINUS;
}

bool Symbol::isStar() {
    return _type == SYM_STAR;
}
bool Symbol::isSlash() {
    return _type == SYM_SLASH;
}
bool Symbol::isModulo() {
    return _type == SYM_MODULO;
}
bool Symbol::isGreaterThan() {
    return _type == SYM_GREATER_THAN;
}
bool Symbol::isLessThan() {
    return _type == SYM_LESS_THAN;
}
bool Symbol::isGreaterThanOrEqual() {
    return _type == SYM_GREATER_THAN_OR_EQUAL;
}
bool Symbol::isLessThanOrEqual() {
    return _type == SYM_LESS_THAN_OR_EQUAL;
}

bool Symbol::isEqualityOperator() {
    return _type == SYM_EQUAL_EQUAL;
}

bool Symbol::isInequalityOperator() {
    return _type == SYM_BANG_EQUAL;
}

bool Symbol::isLogicalOperator() {
    return _type == SYM_AND || _type == SYM_OR;
}

bool Symbol::isUnaryOperator() {
    return _type == SYM_BANG;
}

bool Symbol::isFunction() {
    return _type == SYM_FUNCTION;
}

bool Symbol::isReturn() {
    return _type == SYM_RETURN;
}

bool Symbol::isProcedure() {
    return _type == SYM_PROCEDURE;
}

bool Symbol::isType() {
    return _type == SYM_INT_TYPE ||
            _type == SYM_FLOAT_TYPE ||
            _type == SYM_STRING_TYPE ||
            _type == SYM_CHAR_TYPE ||
            _type == SYM_BOOLEAN_TYPE ||
            _type == SYM_ARRAY_TYPE ||
            _type == SYM_VOID_TYPE;
}

SymbolType Symbol::getType() {
    return _type;
}

std::string Symbol::toString() {
    return _toStringValue;
}