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
    std::shared_ptr<IRPointerType> _irType;
    std::shared_ptr<IRInvocableType> _lambdaVariableType;
    std::optional<std::shared_ptr<IRStructType>> _lambdaScopeType;
    std::shared_ptr<IRInvocableParameterListType> _parameterList;
    std::shared_ptr<IRType> _returnType;
public:
    IRLambdaType(llvm::FunctionType* type, std::shared_ptr<IRPointerType> irType, std::shared_ptr<IRInvocableType> lambdaVariableType, std::shared_ptr<IRInvocableParameterListType> parameterList, std::shared_ptr<IRType> returnType, std::optional<std::shared_ptr<IRStructType>> lambdaScopeType = {});
    bool isLambdaType() override;
    bool isFunctionType() override;
    std::optional<std::shared_ptr<IRStructType>> getLambdaScopeType();
    std::shared_ptr<IRInvocableType> getLambdaVariableType();
    llvm::PointerType* getFunctionPointerType();
    llvm::FunctionType* getFunctionType();
    std::shared_ptr<IRTypeValueInstructionNode> getValue() override;
    bool containsTypeThatRequiresFreeing() override;
    bool isInvocableType() override;
    llvm::Type* getType() override;
    llvm::Align getAlignment() override;
    uint64_t getSizeInBytes() override;
    std::shared_ptr<IRType> clone() override;
    void print() override;
};

#endif //JETLANG_IR_LAMBDA_TYPE_H
