//
// Created by Johny Georges on 2025-11-08.
//

#ifndef JETLANG_IR_INVOCABLE_PARAMETER_LIST_TYPE_H
#define JETLANG_IR_INVOCABLE_PARAMETER_LIST_TYPE_H

#include <llvm/IR/Type.h>
#include "ir-parameter-type.h"

class IRInvocableParameterListType {
private:
    std::vector<std::shared_ptr<IRType>> _parameters;
    std::optional<std::shared_ptr<IRType>> _lambdaScopeParameterType = {};
public:
    IRInvocableParameterListType();
    explicit IRInvocableParameterListType(std::vector<std::shared_ptr<IRType>> parameters, std::optional<std::shared_ptr<IRType>> lambdaScopeParameterType = {});
    std::string getId();
    std::vector<std::shared_ptr<IRType>>* getParameters();
    std::vector<llvm::Type*> getParameterTypes();
    std::shared_ptr<IRInvocableParameterListType> clone();
};

#endif //JETLANG_IR_INVOCABLE_PARAMETER_LIST_TYPE_H
