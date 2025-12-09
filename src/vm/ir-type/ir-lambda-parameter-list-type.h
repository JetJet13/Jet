//
// Created by Johny Georges on 2025-11-08.
//

#ifndef JETLANG_IR_LAMBDA_PARAMETER_LIST_TYPE_H
#define JETLANG_IR_LAMBDA_PARAMETER_LIST_TYPE_H

#include <llvm/IR/Type.h>
#include "ir-parameter-type.h"

class IRLambdaParameterListType {
private:
    std::vector<IRType*> _parameters;
    std::optional<IRType*> _lambdaScopeParameterType;
public:
    explicit IRLambdaParameterListType(std::vector<IRType*> parameters, std::optional<IRType*> lambdaScopeParameterType = {});
    std::string getId();
    std::vector<IRType*>* getParameters();
    std::vector<llvm::Type*> getParameterTypes();
    IRLambdaParameterListType* clone();
};

#endif //JETLANG_IR_LAMBDA_PARAMETER_LIST_TYPE_H
