//
// Created by Johny Georges on 2024-06-20.
//

#ifndef JETLANG_ADDRESS_SPACE_GENERATOR_H
#define JETLANG_ADDRESS_SPACE_GENERATOR_H

#include "../../ir-type/ir-type.h"

class AddressSpaceGenerator {
public:
    unsigned int static generate(IRType* type);
};

#endif //JETLANG_ADDRESS_SPACE_GENERATOR_H
