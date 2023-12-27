//
// Created by Johny Georges on 2023-12-24.
//

#ifndef JETLANG_INT_SYMBOL_H
#define JETLANG_INT_SYMBOL_H

#include <string>
#include "../symbol.h"

class IntSymbol : public Symbol {
public:
    IntSymbol();
    std::string toString() override;
};

#endif //JETLANG_INT_SYMBOL_H
