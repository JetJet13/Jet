//
// Created by Johny Georges on 2024-11-26.
//

#ifndef JETLANG_IR_FUNCTION_PARAMETER_TYPE_H
#define JETLANG_IR_FUNCTION_PARAMETER_TYPE_H

#include <llvm/IR/Value.h>
#include "ir-type.h"
#include "ir-pointer-type.h"
#include "ir-function-type.h"

class IRFunctionParameterType : public IRType {
private:
    llvm::StructType* _type;
    IRPointerType* _irFunctionPointer;
    unsigned int _functionIndex;
    unsigned int _functionScopeArgumentIndex;
public:
    explicit IRFunctionParameterType(llvm::StructType* type, IRPointerType* irFunctionPointer);
    llvm::StructType* getType() override;
    bool isFunctionParameterType() override;
    [[nodiscard]] unsigned int getFunctionIndex() const;
    [[nodiscard]] unsigned int getFunctionScopeArgumentIndex() const;
    llvm::PointerType* getFunctionScopeArgumentType();
    llvm::FunctionType* getFunctionType();
    IRFunctionType* getIRFunctionType();
    IRPointerType* getIRFunctionPointer();
    std::string getFunctionParameterName(std::string parameterName);
    std::string getFunctionScopeArgumentParameterName(std::string parameterName);
    uint64_t getSizeInBytes() override;
};

#endif //JETLANG_IR_FUNCTION_PARAMETER_TYPE_H
