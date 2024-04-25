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
    Symbol* createFunctionSymbol();
    Symbol* createReturnSymbol();
    Symbol* createProcedureSymbol();
    Symbol* createEnumSymbol();
    Symbol* createTupleSymbol();
    Symbol* createIfSymbol();
    Symbol* createElseSymbol();
    Symbol* createForSymbol();
    Symbol* createInSymbol();
    Symbol* createWhileSymbol();
    Symbol* createBreakSymbol();
    Symbol* createSkipSymbol();
    Symbol* createTrySymbol();
    Symbol* createCatchSymbol();
    Symbol* createFinallySymbol();
    Symbol* createFatArrowSymbol();
    Symbol* createVoidTypeSymbol();
    Symbol* createIntTypeSymbol();
    Symbol* createFloatTypeSymbol();
    Symbol* createStringTypeSymbol();
    Symbol* createCharTypeSymbol();
    Symbol* createBooleanTypeSymbol();
    Symbol* createArrayTypeSymbol();
    Symbol* createModuleSymbol();
    Symbol* createAsSymbol();
    Symbol* createImportSymbol();
    Symbol* createUseSymbol();
    Symbol* createFromSymbol();
    Symbol* createDotDotSymbol();
    Symbol* createDotDotDotSymbol();
    Symbol* createColonColonSymbol();
    Symbol* createClassSymbol();
    Symbol* createPublicSymbol();
    Symbol* createProtectedSymbol();
    Symbol* createPrivateSymbol();
    Symbol* createStaticSymbol();
    Symbol* createThisSymbol();
    Symbol* createConstructorSymbol();
}


#endif //JETLANG_SYMBOL_FACTORY_H
