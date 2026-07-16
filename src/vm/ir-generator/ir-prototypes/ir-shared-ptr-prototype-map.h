//
// Created by Johny Georges on 2025-10-25.
//

#ifndef JETLANG_IR_SHARED_PTR_PROTOTYPE_MAP_H
#define JETLANG_IR_SHARED_PTR_PROTOTYPE_MAP_H

#include <string>
#include <optional>
#include "../../types/ir-shared-ptr-prototype-function.h"

class SharedPtrPrototypeMap {
public:
    static std::optional<IRSharedPtrPrototypeFunctionId> getIRSharedPtrPrototypeFunction(std::string id);
    static std::string getIRName(IRSharedPtrPrototypeFunctionId irSharedPtrPrototypeFunction);
    static std::optional<std::string> getIRName(const std::string& id);
};

#endif //JETLANG_IR_SHARED_PTR_PROTOTYPE_MAP_H