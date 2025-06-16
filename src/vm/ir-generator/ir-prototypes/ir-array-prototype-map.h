//
// Created by Johny Georges on 2025-06-16.
//

#ifndef JETLANG_IR_ARRAY_PROTOTYPE_MAP_H
#define JETLANG_IR_ARRAY_PROTOTYPE_MAP_H

#include <string>
#include "../../types/ir-array-prototype-function.h"

class ArrayPrototypeMap {
public:
    ArrayPrototypeMap();
    static IRArrayPrototypeFunctionId getIRArrayPrototypeFunction(std::string id);
    static std::string getIRName(IRArrayPrototypeFunctionId irArrayPrototypeFunction);
    static std::string getIRName(std::string id);
};

#endif //JETLANG_IR_ARRAY_PROTOTYPE_MAP_H
