//
// Created by Johny Georges on 2023-12-24.
//

#include <string>
#include "int-symbol.h"

IntSymbol::IntSymbol() {
    _value = "INT_SYMBOL";
}

std::string IntSymbol::toString() {
    return _value;
}
