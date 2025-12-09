//
// Created by Johny Georges on 2024-11-12.
//

#ifndef JETLANG_IR_LAMBDA_TYPE_H
#define JETLANG_IR_LAMBDA_TYPE_H

#include "ir-struct-type.h"
#include "ir-function-parameter-type.h"
#include "ir-lambda-parameter-list-type.h"

class IRLambdaType : public IRType {
private:
    llvm::FunctionType* _type;
    IRPointerType* _irType;
    IRFunctionParameterType* _lambdaVariableType;
    std::optional<IRStructType*> _lambdaScopeType;
    IRLambdaParameterListType* _parameterList;
    IRType* _returnType;
public:
    IRLambdaType(llvm::FunctionType* type, IRPointerType* irType, IRFunctionParameterType* lambdaVariableType, IRLambdaParameterListType* parameterList, IRType* returnType, std::optional<IRStructType*> lambdaScopeType = {});
    bool isLambdaType() override;
    bool isFunctionType() override;
    std::optional<IRStructType*> getLambdaScopeType();
    IRFunctionParameterType* getLambdaVariableType();
    llvm::PointerType* getFunctionPointerType();
    llvm::FunctionType* getType() override;
    llvm::Align getAlignment() override;
    void print() override;
};

#endif //JETLANG_IR_LAMBDA_TYPE_H
