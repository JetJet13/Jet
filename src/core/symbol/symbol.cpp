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

bool Symbol::isEnum() {
    return _type == SYM_ENUM;
}

bool Symbol::isTuple() {
    return _type == SYM_TUPLE;
}

bool Symbol::isIf() {
    return _type == SYM_IF;
}

bool Symbol::isElse() {
    return _type == SYM_ELSE;
}

bool Symbol::isFor() {
    return _type == SYM_FOR;
}

bool Symbol::isIn() {
    return _type == SYM_IN;
}

bool Symbol::isWhile() {
    return _type == SYM_WHILE;
}

bool Symbol::isBreak() {
    return _type == SYM_BREAK;
}

bool Symbol::isSkip() {
    return _type == SYM_SKIP;
}

bool Symbol::isTry() {
    return _type == SYM_TRY;
}

bool Symbol::isCatch() {
    return _type == SYM_CATCH;
}

bool Symbol::isFinally() {
    return _type == SYM_FINALLY;
}

bool Symbol::isFatArrow() {
    return _type == SYM_FAT_ARROW;
}

bool Symbol::isArrayTypeKeyword() {
    return _type == SYM_ARRAY_TYPE;
}

bool Symbol::isType() {
    return _type == SYM_INT_TYPE ||
            _type == SYM_FLOAT_TYPE ||
            _type == SYM_STRING_TYPE ||
            _type == SYM_CHAR_TYPE ||
            _type == SYM_BOOLEAN_TYPE ||
            _type == SYM_VOID_TYPE;
}

bool Symbol::isModule() {
    return _type == SYM_MODULE;
}

bool Symbol::isAsKeyword() {
    return _type == SYM_AS;
}

bool Symbol::isImport() {
    return _type == SYM_IMPORT;
}

bool Symbol::isFromKeyword() {
    return _type == SYM_FROM;
}

bool Symbol::isDotDot() {
    return _type == SYM_DOT_DOT;
}

bool Symbol::isDotDotDot() {
    return _type == SYM_DOT_DOT_DOT;
}

bool Symbol::isColonColon() {
    return _type == SYM_COLON_COLON;
}

bool Symbol::isUseKeyword() {
    return _type == SYM_USE;
}

bool Symbol::isClass() {
    return _type == SYM_CLASS;
}

bool Symbol::isPublic() {
    return _type == SYM_PUBLIC;
}

bool Symbol::isProtected() {
    return _type == SYM_PROTECTED;
}

bool Symbol::isPrivate() {
    return _type == SYM_PRIVATE;
}

bool Symbol::isStatic() {
    return _type == SYM_STATIC;
}

bool Symbol::isConstructor() {
    return _type == SYM_CONSTRUCTOR;
}

bool Symbol::isThis() {
    return _type == SYM_THIS;
}

SymbolType Symbol::getType() {
    return _type;
}

std::string Symbol::toString() {
    return _toStringValue;
}