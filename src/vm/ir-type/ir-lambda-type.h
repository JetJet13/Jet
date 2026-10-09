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
