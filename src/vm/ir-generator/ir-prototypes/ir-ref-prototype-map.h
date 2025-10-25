//
// Created by Johny Georges on 2025-10-25.
//

#ifndef JETLANG_IR_REF_PROTOTYPE_MAP_H
#define JETLANG_IR_REF_PROTOTYPE_MAP_H

#include <string>
#include "../../types/ir-ref-prototype-function.h"

class RefPrototypeMap {
public:
    RefPrototypeMap();
    static IRRefPrototypeFunctionId getIRRefPrototypeFunction(std::string id);
    static std::string getIRName(IRRefPrototypeFunctionId irRefPrototypeFunction);
    static std::string getIRName(std::string id);
};

#endif //JETLANG_IR_REF_PROTOTYPE_MAP_H
