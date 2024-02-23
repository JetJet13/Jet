//
// Created by Johny Georges on 2023-12-27.
//

#ifndef JETLANG_SYMBOL_FACTORY_H
#define JETLANG_SYMBOL_FACTORY_H

#include "symbol.h"


namespace SymbolFactory {
    Symbol* createIdentifierSymbol();
    Symbol* createIntSymbol();
    Symbol* createFloatSymbol();
    Symbol* createEqualSymbol();
    Symbol* createVarSymbol();
    Symbol* createConstSymbol();
    Symbol* createSemicolonSymbol();
    Symbol* createModuloSymbol();
    Symbol* createPlusSymbol();
    Symbol* createMinusSymbol();
    Symbol* createStarSymbol();
    Symbol* createSlashSymbol();
    Symbol* createLessThanSymbol();
    Symbol* createLessThanOrEqualSymbol();
    Symbol* createGreaterThanSymbol();
    Symbol* createGreaterThanOrEqualSymbol();
    Symbol* createTrueSymbol();
    Symbol* createFalseSymbol();
    Symbol* createAndSymbol();
    Symbol* createOrSymbol();
    Symbol* createLeftParenSymbol();
    Symbol* createRightParenSymbol();
    Symbol* createLeftBraceSymbol();
    Symbol* createRightBraceSymbol();
    Symbol* createLeftBracketSymbol();
    Symbol* createRightBracketSymbol();
    Symbol* createColonSymbol();
    Symbol* createCommaSymbol();
    Symbol* createPeriodSymbol();
    Symbol* createBangSymbol();
    Symbol* createBangEqualSymbol();
    Symbol* createEqualEqualSymbol();
    Symbol* createCharSymbol();
    Symbol* createStringSymbol();
    Symbol* createMalformedSymbol();
}


#endif //JETLANG_SYMBOL_FACTORY_H
