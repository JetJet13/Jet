//
// Created by Johny Georges on 2024-07-12.
//

#ifndef JETLANG_IR_PARAMETER_LIST_TYPE_H
#define JETLANG_IR_PARAMETER_LIST_TYPE_H

#include <llvm/IR/Type.h>
#include "ir-parameter-type.h"

class IRParameterListType {
private:
    std::vector<IRParameterType*> _parameters;
public:
    explicit IRParameterListType(std::vector<IRParameterType*> parameters);
    std::vector<IRParameterType*>* getParameters();
    std::vector<llvm::Type*> getParameterTypes();
};

#endif //JETLANG_IR_PARAMETER_LIST_TYPE_H
