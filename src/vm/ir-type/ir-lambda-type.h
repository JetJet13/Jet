//
// Created by Johny Georges on 2024-11-12.
//

#ifndef JETLANG_IR_LAMBDA_TYPE_H
#define JETLANG_IR_LAMBDA_TYPE_H

#include "ir-struct-type.h"
#include "ir-invocable-type.h"
#include "ir-invocable-parameter-list-type.h"

class IRLambdaType : public IRType {
private:
    llvm::FunctionType* _type;
    IRPointerType* _irType;
    IRInvocableType* _lambdaVariableType;
    std::optional<IRStructType*> _lambdaScopeType;
    IRInvocableParameterListType* _parameterList;
    IRType* _returnType;
public:
    IRLambdaType(llvm::FunctionType* type, IRPointerType* irType, IRInvocableType* lambdaVariableType, IRInvocableParameterListType* parameterList, IRType* returnType, std::optional<IRStructType*> lambdaScopeType = {});
    bool isLambdaType() override;
    bool isFunctionType() override;
    std::optional<IRStructType*> getLambdaScopeType();
    IRInvocableType* getLambdaVariableType();
    llvm::PointerType* getFunctionPointerType();
    bool containsTypeThatRequiresFreeing() override;
    bool isInvocableType() override;
    llvm::FunctionType* getType() override;
    llvm::Align getAlignment() override;
    IRLambdaType* clone() override;
    void print() override;
};

#endif //JETLANG_IR_LAMBDA_TYPE_H
