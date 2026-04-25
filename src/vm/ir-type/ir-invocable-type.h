//
// Created by Johny Georges on 2024-11-26.
//

#ifndef JETLANG_IR_INVOCABLE_TYPE_H
#define JETLANG_IR_INVOCABLE_TYPE_H

#include <llvm/IR/Value.h>
#include "ir-type.h"
#include "ir-pointer-type.h"
#include "ir-function-type.h"
#include "ir-parameter-list-type.h"
#include "ir-invocable-parameter-list-type.h"

class IRInvocableType : public IRType {
private:
    llvm::StructType* _type;
    IRPointerType* _irFunctionPointer;
    IRPointerType* _irFunctionCleanupPointer;
    IRInvocableParameterListType* _parameters;
    IRType* _returnType;
    unsigned int _functionIndex;
    unsigned int _functionScopeArgumentIndex;
    unsigned int _functionRefCounterIndex;
    unsigned int _functionCleanupIndex;
    unsigned int _isPerpetualIndex;
public:
    explicit IRInvocableType(llvm::StructType* type, IRPointerType* irFunctionPointer, IRPointerType* irFunctionCleanupPointer, IRInvocableParameterListType* parameters, IRType* returnType);
    llvm::StructType* getType() override;
    bool isInvocableType() override;
    [[nodiscard]] unsigned int getFunctionIndex() const;
    [[nodiscard]] unsigned int getFunctionScopeArgumentIndex() const;
    [[nodiscard]] unsigned int getFunctionRefCounterIndex() const;
    [[nodiscard]] unsigned int getFunctionCleanupIndex() const;
    [[nodiscard]] unsigned int getIsPerpetualIndex() const;
    IRInvocableParameterListType* getParameters();
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
    bool containsTypeThatRequiresFreeing() override;
    bool requiresArc() override;
    llvm::Align getAlignment() override;
    uint64_t getSizeInBytes() override;
    IRInvocableType* clone() override;
};

#endif //JETLANG_IR_INVOCABLE_TYPE_H
