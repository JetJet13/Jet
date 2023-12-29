//
// Created by Johny Georges on 2023-12-27.
//

#ifndef JETLANG_SYMBOL_FACTORY_H
#define JETLANG_SYMBOL_FACTORY_H

#include "symbol.h"


namespace SymbolFactory {
    Symbol* createIdentifierSymbol();
    Symbol* createIntSymbol();
    Symbol* createEqualSymbol();
    Symbol* createVarSymbol();
    Symbol* createConstSymbol();
    Symbol* createSemicolonSymbol();
}


#endif //JETLANG_SYMBOL_FACTORY_H
