//
// Created by Johny Georges on 2024-07-12.
//

#ifndef JETLANG_IR_PARAMETER_LIST_TYPE_H
#define JETLANG_IR_PARAMETER_LIST_TYPE_H

#include <llvm/IR/Type.h>
#include "ir-parameter-type.h"

class IRParameterListType {
private:
    std::vector<std::shared_ptr<IRParameterType>> _parameters;
public:
    explicit IRParameterListType(std::vector<std::shared_ptr<IRParameterType>> parameters);
    std::vector<std::shared_ptr<IRParameterType>>* getParameters();
    std::vector<llvm::Type*> getParameterTypes();
    std::shared_ptr<IRParameterListType> clone();
};

#endif //JETLANG_IR_PARAMETER_LIST_TYPE_H
