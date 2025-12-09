//
// Created by Johny Georges on 2024-11-26.
//

#ifndef JETLANG_IR_FUNCTION_PARAMETER_TYPE_H
#define JETLANG_IR_FUNCTION_PARAMETER_TYPE_H

#include <llvm/IR/Value.h>
#include "ir-type.h"
#include "ir-pointer-type.h"
#include "ir-function-type.h"
#include "ir-parameter-list-type.h"
#include "ir-lambda-parameter-list-type.h"

class IRFunctionParameterType : public IRType {
private:
    llvm::StructType* _type;
    IRPointerType* _irFunctionPointer;
    IRPointerType* _irFunctionCleanupPointer;
    IRLambdaParameterListType* _parameters;
    IRType* _returnType;
    unsigned int _functionIndex;
    unsigned int _functionScopeArgumentIndex;
    unsigned int _functionRefCounterIndex;
    unsigned int _functionCleanupIndex;
public:
    explicit IRFunctionParameterType(llvm::StructType* type, IRPointerType* irFunctionPointer, IRPointerType* irFunctionCleanupPointer, IRLambdaParameterListType* parameters, IRType* returnType);
    llvm::StructType* getType() override;
    bool isFunctionParameterType() override;
    [[nodiscard]] unsigned int getFunctionIndex() const;
    [[nodiscard]] unsigned int getFunctionScopeArgumentIndex() const;
    [[nodiscard]] unsigned int getFunctionRefCounterIndex() const;
    [[nodiscard]] unsigned int getFunctionCleanupIndex() const;
    IRLambdaParameterListType* getParameters();
    IRType* getReturnType();
    llvm::PointerType* getFunctionScopeArgumentType();
    llvm::PointerType* getFunctionRefCounterType();
    llvm::PointerType* getFunctionCleanupType();
    llvm::FunctionType* getFunctionType();
    llvm::FunctionType* getCleanupFunctionType();
    IRFunctionType* getIRFunctionType();
    IRPointerType* getIRFunctionPointer();
    std::string getFunctionParameterName(std::string parameterName);
    std::string getFunctionScopeArgumentParameterName(std::string parameterName);
    uint64_t getRefCounterSizeInBytes();
    uint64_t getCleanupFunctionSizeInBytes();
    llvm::Align getAlignment() override;
    uint64_t getSizeInBytes() override;
};

#endif //JETLANG_IR_FUNCTION_PARAMETER_TYPE_H
