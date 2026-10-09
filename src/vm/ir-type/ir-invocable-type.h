// Copyright 2026 Johny Georges
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

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
    std::shared_ptr<IRPointerType> _irFunctionPointer;
    std::shared_ptr<IRPointerType> _irFunctionCleanupPointer;
    std::shared_ptr<IRInvocableParameterListType> _parameters;
    std::shared_ptr<IRType> _returnType;
    unsigned int _functionIndex;
    unsigned int _functionScopeArgumentIndex;
    unsigned int _functionRefCounterIndex;
    unsigned int _functionCleanupIndex;
    unsigned int _isPerpetualIndex;
public:
    explicit IRInvocableType(llvm::StructType* type, std::shared_ptr<IRPointerType> irFunctionPointer, std::shared_ptr<IRPointerType> irFunctionCleanupPointer, std::shared_ptr<IRInvocableParameterListType> parameters, std::shared_ptr<IRType> returnType);
    llvm::StructType* getType() override;
    bool isInvocableType() override;
    [[nodiscard]] unsigned int getFunctionIndex() const;
    [[nodiscard]] unsigned int getFunctionScopeArgumentIndex() const;
    [[nodiscard]] unsigned int getFunctionRefCounterIndex() const;
    [[nodiscard]] unsigned int getFunctionCleanupIndex() const;
    [[nodiscard]] unsigned int getIsPerpetualIndex() const;
    std::shared_ptr<IRInvocableParameterListType> getParameters();
    std::shared_ptr<IRType> getReturnType();
    llvm::PointerType* getFunctionScopeArgumentType();
    llvm::PointerType* getFunctionRefCounterType();
    llvm::PointerType* getFunctionCleanupType();
    llvm::FunctionType* getFunctionType();
    llvm::FunctionType* getCleanupFunctionType();
    std::shared_ptr<IRFunctionType> getIRFunctionType();
    std::shared_ptr<IRPointerType> getIRFunctionPointer();
    std::string getFunctionParameterName(std::string parameterName);
    std::string getFunctionScopeArgumentParameterName(std::string parameterName);
    uint64_t getRefCounterSizeInBytes();
    uint64_t getCleanupFunctionSizeInBytes();
    bool containsTypeThatRequiresFreeing() override;
    bool requiresArc() override;
    llvm::Align getAlignment() override;
    uint64_t getSizeInBytes() override;
    std::shared_ptr<IRType> clone() override;
};

#endif //JETLANG_IR_INVOCABLE_TYPE_H
