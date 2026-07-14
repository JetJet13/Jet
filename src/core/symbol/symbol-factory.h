//
// Created by Johny Georges on 2023-12-27.
//

#ifndef JETLANG_SYMBOL_FACTORY_H
#define JETLANG_SYMBOL_FACTORY_H

#include "symbol.h"
#include <memory>

namespace SymbolFactory {
    std::shared_ptr<Symbol> createIdentifierSymbol();
    std::shared_ptr<Symbol> createIntSymbol();
    std::shared_ptr<Symbol> createFloatSymbol();
    std::shared_ptr<Symbol> createEqualSymbol();
    std::shared_ptr<Symbol> createColonEqualSymbol();
    std::shared_ptr<Symbol> createLetSymbol();
    std::shared_ptr<Symbol> createConstSymbol();
    std::shared_ptr<Symbol> createSemicolonSymbol();
    std::shared_ptr<Symbol> createModuloSymbol();
    std::shared_ptr<Symbol> createPlusSymbol();
    std::shared_ptr<Symbol> createMinusSymbol();
    std::shared_ptr<Symbol> createStarSymbol();
    std::shared_ptr<Symbol> createSlashSymbol();
    std::shared_ptr<Symbol> createLessThanSymbol();
    std::shared_ptr<Symbol> createLessThanOrEqualSymbol();
    std::shared_ptr<Symbol> createGreaterThanSymbol();
    std::shared_ptr<Symbol> createGreaterThanOrEqualSymbol();
    std::shared_ptr<Symbol> createTrueSymbol();
    std::shared_ptr<Symbol> createFalseSymbol();
    std::shared_ptr<Symbol> createAndSymbol();
    std::shared_ptr<Symbol> createOrSymbol();
    std::shared_ptr<Symbol> createLeftParenSymbol();
    std::shared_ptr<Symbol> createRightParenSymbol();
    std::shared_ptr<Symbol> createLeftBraceSymbol();
    std::shared_ptr<Symbol> createRightBraceSymbol();
    std::shared_ptr<Symbol> createLeftBracketSymbol();
    std::shared_ptr<Symbol> createRightBracketSymbol();
    std::shared_ptr<Symbol> createColonSymbol();
    std::shared_ptr<Symbol> createCommaSymbol();
    std::shared_ptr<Symbol> createPeriodSymbol();
    std::shared_ptr<Symbol> createBangSymbol();
    std::shared_ptr<Symbol> createBangEqualSymbol();
    std::shared_ptr<Symbol> createEqualEqualSymbol();
    std::shared_ptr<Symbol> createCharSymbol();
    std::shared_ptr<Symbol> createStringSymbol();
    std::shared_ptr<Symbol> createMalformedSymbol(std::string malformedText);
    std::shared_ptr<Symbol> createFunctionSymbol();
    std::shared_ptr<Symbol> createReturnSymbol();
    std::shared_ptr<Symbol> createProcedureSymbol();
    std::shared_ptr<Symbol> createEnumSymbol();
    std::shared_ptr<Symbol> createTupleSymbol();
    std::shared_ptr<Symbol> createIfSymbol();
    std::shared_ptr<Symbol> createElseSymbol();
    std::shared_ptr<Symbol> createForSymbol();
    std::shared_ptr<Symbol> createInSymbol();
    std::shared_ptr<Symbol> createWhileSymbol();
    std::shared_ptr<Symbol> createBreakSymbol();
    std::shared_ptr<Symbol> createSkipSymbol();
    std::shared_ptr<Symbol> createTrySymbol();
    std::shared_ptr<Symbol> createCatchSymbol();
    std::shared_ptr<Symbol> createFinallySymbol();
    std::shared_ptr<Symbol> createFatArrowSymbol();
    std::shared_ptr<Symbol> createVoidSymbol();
    std::shared_ptr<Symbol> createIntTypeSymbol();
    std::shared_ptr<Symbol> createFloatTypeSymbol();
    std::shared_ptr<Symbol> createStringTypeSymbol();
    std::shared_ptr<Symbol> createCharTypeSymbol();
    std::shared_ptr<Symbol> createBooleanTypeSymbol();
    std::shared_ptr<Symbol> createModuleSymbol();
    std::shared_ptr<Symbol> createAsSymbol();
    std::shared_ptr<Symbol> createImportSymbol();
    std::shared_ptr<Symbol> createUseSymbol();
    std::shared_ptr<Symbol> createFromSymbol();
    std::shared_ptr<Symbol> createDotDotSymbol();
    std::shared_ptr<Symbol> createDotDotDotSymbol();
    std::shared_ptr<Symbol> createColonColonSymbol();
    std::shared_ptr<Symbol> createClassSymbol();
    std::shared_ptr<Symbol> createPublicSymbol();
    std::shared_ptr<Symbol> createProtectedSymbol();
    std::shared_ptr<Symbol> createPrivateSymbol();
    std::shared_ptr<Symbol> createStaticSymbol();
    std::shared_ptr<Symbol> createThisSymbol();
    std::shared_ptr<Symbol> createConstructorSymbol();
    std::shared_ptr<Symbol> createNewSymbol();
    std::shared_ptr<Symbol> createExportSymbol();
    std::shared_ptr<Symbol> createRefSymbol();
    std::shared_ptr<Symbol> createDrefSymbol();
    std::shared_ptr<Symbol> createShareSymbol();
    std::shared_ptr<Symbol> createSharedSymbol();
    std::shared_ptr<Symbol> createConcatSymbol();
    std::shared_ptr<Symbol> createInterfaceSymbol();
    std::shared_ptr<Symbol> createImplementsSymbol();
    std::shared_ptr<Symbol> createTypeSymbol();
}


#endif //JETLANG_SYMBOL_FACTORY_H
