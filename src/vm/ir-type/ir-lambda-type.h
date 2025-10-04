//
// Created by Johny Georges on 2024-11-12.
//

#ifndef JETLANG_IR_LAMBDA_TYPE_H
#define JETLANG_IR_LAMBDA_TYPE_H

#include "ir-struct-type.h"
#include "ir-function-parameter-type.h"

class IRLambdaType : public IRType {
private:
    llvm::FunctionType* _type;
    IRPointerType* _irType;
    IRFunctionParameterType* _lambdaVariableType;
    std::optional<IRType*> _lambdaScopeType;
public:
    IRLambdaType(llvm::FunctionType* type, IRPointerType* irType, IRFunctionParameterType* lambdaVariableType, std::optional<IRType*> lambdaScopeType = {});
    bool isLambdaType() override;
    bool isFunctionType() override;
    std::optional<IRType*> getLambdaScopeType();
    IRFunctionParameterType* getLambdaVariableType();
    llvm::PointerType* getFunctionPointerType();
    llvm::FunctionType* getType() override;
    llvm::Align getAlignment() override;
    void print() override;
};

#endif //JETLANG_IR_LAMBDA_TYPE_H
