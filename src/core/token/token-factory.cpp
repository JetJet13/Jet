//
// Created by Johny Georges on 2023-12-27.
//

#include "token-factory.h"
#include "../symbol/symbol-factory.h"
#include "../../shared/types/null-type.h"

namespace TokenFactory {

    Token<int>* createIntToken(int value) {
        return new Token<int>(
                SymbolFactory::createIntSymbol(),
                value
        );
    }

    Token<NullType>* createEqualToken() {
        return new Token<NullType>(
                SymbolFactory::createEqualSymbol()
        );
    }
}


