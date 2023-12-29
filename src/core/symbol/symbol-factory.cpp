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
        return new Symbol(SYM_VAR, "var");
    }


}