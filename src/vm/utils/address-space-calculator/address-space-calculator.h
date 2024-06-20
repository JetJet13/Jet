//
// Created by Johny Georges on 2024-06-20.
//

#ifndef JETLANG_ADDRESS_SPACE_CALCULATOR_H
#define JETLANG_ADDRESS_SPACE_CALCULATOR_H

#include "../../ir-type/ir-type.h"

class AddressSpaceCalculator {
public:
    unsigned int static calculate(IRType* type);
};

#endif //JETLANG_ADDRESS_SPACE_CALCULATOR_H
