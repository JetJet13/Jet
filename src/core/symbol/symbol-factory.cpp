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

    Symbol* createSemicolonSymbol() {
        return new Symbol(SYM_SEMICOLON, ";");
    }

    Symbol* createVarSymbol() {
        return new Symbol(SYM_LET, "let");
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

    Symbol* createLessThenSymbol() {
        return new Symbol(SYM_LESS_THEN, "<");
    }

    Symbol* createGreaterThenSymbol() {
        return new Symbol(SYM_GREATER_THEN, ">");
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
}