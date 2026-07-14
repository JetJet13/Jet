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
    bool isComma();
    bool isColon();
    bool isPeriod();
    bool isLeftBracket();
    bool isRightBracket();
    bool isLeftBrace();
    bool isRightBrace();
    bool isLeftParentheses();
    bool isRightParentheses();
    bool isMalformed();
    bool isBang();
    bool isEqual();
    bool isColonEqual();
    bool isInt();
    bool isFloat();
    bool isChar();
    bool isLet();
    bool isConst();
    bool isString();
    bool isIdentifier();
    bool isBoolean();
    bool isTrue();
    bool isFalse();
    bool isPlus();
    bool isMinus();
    bool isStar();
    bool isSlash();
    bool isModulo();
    bool isGreaterThan();
    bool isLessThan();
    bool isGreaterThanOrEqual();
    bool isLessThanOrEqual();
    bool isEqualityOperator();
    bool isInequalityOperator();
    bool isAnd();
    bool isOr();
    bool isLogicalOperator();
    bool isUnaryOperator();
    bool isFunction();
    bool isReturn();
    bool isType();
    bool isIntType();
    bool isFloatType();
    bool isStringType();
    bool isCharType();
    bool isBooleanType();
    bool isVarTypeQualifier();
    bool isProcedure();
    bool isEnum();
    bool isTuple();
    bool isIf();
    bool isElse();
    bool isFor();
    bool isIn();
    bool isWhile();
    bool isBreak();
    bool isSkip();
    bool isTry();
    bool isCatch();
    bool isFinally();
    bool isFatArrow();
    bool isModule();
    bool isAsKeyword();
    bool isImport();
    bool isFromKeyword();
    bool isDotDot();
    bool isDotDotDot();
    bool isColonColon();
    bool isUseKeyword();
    bool isClass();
    bool isPublic();
    bool isProtected();
    bool isPrivate();
    bool isStatic();
    bool isConstructor();
    bool isNew();
    bool isExport();
    bool isShare();
    bool isShared();
    bool isRef();
    bool isDref();
    bool isConcat();
    bool isInterface();
    bool isImplements();
    bool isTypeKeyword();
    bool isVoid();
    bool isPrint();
    bool isThis();
    SymbolType getType();
    bool isSameAs(std::shared_ptr<Symbol> symbol);
    std::string toString();
};

#endif //JETLANG_SYMBOL_H
