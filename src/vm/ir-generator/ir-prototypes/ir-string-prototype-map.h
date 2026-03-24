//
// Created by Johny Georges on 2026-03-21.
//

#ifndef JETLANG_IR_STRING_PROTOTYPE_MAP_H
#define JETLANG_IR_STRING_PROTOTYPE_MAP_H

#include <string>
#include "../../types/ir-string-prototype-function.h"

class StringPrototypeMap {
public:
    StringPrototypeMap();
    static IRStringPrototypeFunctionId getIRStringPrototypeFunction(std::string id);
    static std::string getIRName(IRStringPrototypeFunctionId irStringPrototypeFunction);
    static std::string getIRName(std::string id);
};

#endif //JETLANG_IR_STRING_PROTOTYPE_MAP_H
