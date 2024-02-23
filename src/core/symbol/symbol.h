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
    bool isSemicolon();
    bool isMalformed();
    bool isBang();
    bool isEqual();
    bool isInt();
    bool isFloat();
    bool isChar();
    bool isLet();
    bool isConst();
    bool isString();
    bool isIdentifier();
    bool isBoolean();
    bool isPlus();
    bool isMinus();
    bool isStar();
    bool isSlash();
    bool isModulo();
    bool isGreaterThan();
    bool isLessThan();
    bool isGreaterThanOrEqual();
    bool isLessThanOrEqual();
    bool isArithmeticOperator();
    bool isEqualityOperator();
    bool isInequalityOperator();
    bool isLogicalOperator();
    bool isUnaryOperator();
    bool isVarTypeQualifier();
    SymbolType getType();
    std::string toString();
};

#endif //JETLANG_SYMBOL_H
