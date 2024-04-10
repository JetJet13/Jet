//
// Created by Johny Georges on 2023-12-27.
//

#include "symbol-factory.h"
#include "symbol.h"

namespace SymbolFactory {

    Symbol* createConstSymbol() {
        return new Symbol(SYM_CONST, "const");
    }

    Symbol* createEqualSymbol() {
        return new Symbol(SYM_EQUAL, "=");
    }

    Symbol* createIdentifierSymbol() {
        return new Symbol(SYM_IDENTIFIER, "id");
    }

    Symbol* createIntSymbol() {
        return new Symbol(SYM_INT, "int");
    }

    Symbol* createFloatSymbol() {
        return new Symbol(SYM_FLOAT, "float");
    }

    Symbol* createSemicolonSymbol() {
        return new Symbol(SYM_SEMICOLON, ";");
    }

    Symbol* createVarSymbol() {
        return new Symbol(SYM_LET, "let");
    }

    Symbol* createModuloSymbol() {
        return new Symbol(SYM_MODULO, "mod");
    }

    Symbol* createPlusSymbol() {
        return new Symbol(SYM_PLUS, "+");
    }

    Symbol* createMinusSymbol() {
        return new Symbol(SYM_MINUS, "-");
    }

    Symbol* createStarSymbol() {
        return new Symbol(SYM_STAR, "*");
    }

    Symbol* createSlashSymbol() {
        return new Symbol(SYM_SLASH, "/");
    }

    Symbol* createLessThanSymbol() {
        return new Symbol(SYM_LESS_THAN, "<");
    }

    Symbol* createLessThanOrEqualSymbol() {
        return new Symbol(SYM_LESS_THAN_OR_EQUAL, "<=");
    }

    Symbol* createGreaterThanSymbol() {
        return new Symbol(SYM_GREATER_THAN, ">");
    }

    Symbol* createGreaterThanOrEqualSymbol() {
        return new Symbol(SYM_GREATER_THAN_OR_EQUAL, ">=");
    }

    Symbol* createTrueSymbol() {
        return new Symbol(SYM_TRUE, "true");
    }

    Symbol* createFalseSymbol() {
        return new Symbol(SYM_FALSE, "false");
    }

    Symbol* createAndSymbol() {
        return new Symbol(SYM_AND, "and");
    }

    Symbol* createOrSymbol() {
        return new Symbol(SYM_OR, "or");
    }

    Symbol* createLeftParenSymbol() {
        return new Symbol(SYM_LEFT_PAREN, "(");
    }

    Symbol* createRightParenSymbol() {
        return new Symbol(SYM_RIGHT_PAREN, ")");
    }

    Symbol* createLeftBraceSymbol() {
        return new Symbol(SYM_LEFT_BRACE, "{");
    }

    Symbol* createRightBraceSymbol() {
        return new Symbol(SYM_RIGHT_BRACE, "}");
    }

    Symbol* createLeftBracketSymbol() {
        return new Symbol(SYM_LEFT_BRACKET, "[");
    }

    Symbol* createRightBracketSymbol() {
        return new Symbol(SYM_RIGHT_BRACKET, "]");
    }

    Symbol* createColonSymbol() {
        return new Symbol(SYM_COLON, ":");
    }

    Symbol* createCommaSymbol() {
        return new Symbol(SYM_COMMA, ",");
    }

    Symbol* createPeriodSymbol() {
        return new Symbol(SYM_PERIOD, ".");
    }

    Symbol* createBangSymbol() {
        return new Symbol(SYM_BANG, "!");
    }

    Symbol* createBangEqualSymbol() {
        return new Symbol(SYM_BANG_EQUAL, "!=");
    }

    Symbol* createEqualEqualSymbol() {
        return new Symbol(SYM_EQUAL_EQUAL, "==");
    }

    Symbol* createCharSymbol() {
        return new Symbol(SYM_CHAR, "char");
    }

    Symbol* createStringSymbol() {
        return new Symbol(SYM_STRING, "string");
    }

    Symbol* createMalformedSymbol() {
        return new Symbol(SYM_MALFORMED, "[MALFORMED]");
    }

    Symbol* createFunctionSymbol() {
        return new Symbol(SYM_FUNCTION, "func");
    }

    Symbol* createReturnSymbol() {
        return new Symbol(SYM_RETURN, "return");
    }

    Symbol* createProcedureSymbol() {
        return new Symbol(SYM_PROCEDURE, "proc");
    }

    Symbol* createEnumSymbol() {
        return new Symbol(SYM_ENUM, "enum");
    }

    Symbol* createTupleSymbol() {
        return new Symbol(SYM_TUPLE, "tuple");
    }

    Symbol* createIfSymbol() {
        return new Symbol(SYM_IF, "if");
    }

    Symbol* createElseSymbol() {
        return new Symbol(SYM_ELSE, "else");
    }

    Symbol* createForSymbol() {
        return new Symbol(SYM_FOR, "for");
    }

    Symbol* createInSymbol() {
        return new Symbol(SYM_IN, "in");
    }

    Symbol* createWhileSymbol() {
        return new Symbol(SYM_WHILE, "while");
    }

    Symbol* createBreakSymbol() {
        return new Symbol(SYM_BREAK, "break");
    }

    Symbol* createSkipSymbol() {
        return new Symbol(SYM_SKIP, "skip");
    }

    Symbol* createTrySymbol() {
        return new Symbol(SYM_TRY, "try");
    }

    Symbol* createCatchSymbol() {
        return new Symbol(SYM_CATCH, "catch");
    }

    Symbol* createFinallySymbol() {
        return new Symbol(SYM_FINALLY, "finally");
    }

    Symbol* createFatArrowSymbol() {
        return new Symbol(SYM_FAT_ARROW, "=>");
    }

    Symbol* createArrayTypeSymbol() {
        return new Symbol(SYM_ARRAY_TYPE, "arr");
    }

    Symbol* createVoidTypeSymbol() {
        return new Symbol(SYM_VOID_TYPE, "void_type");
    }

    Symbol* createIntTypeSymbol() {
        return new Symbol(SYM_INT_TYPE, "int_type");
    }

    Symbol* createFloatTypeSymbol() {
        return new Symbol(SYM_FLOAT_TYPE, "float_type");
    }

    Symbol* createStringTypeSymbol() {
        return new Symbol(SYM_STRING_TYPE, "string_type");
    }

    Symbol* createCharTypeSymbol() {
        return new Symbol(SYM_CHAR_TYPE, "char_type");
    }

    Symbol* createBooleanTypeSymbol() {
        return new Symbol(SYM_BOOLEAN_TYPE, "boolean_type");
    }

}