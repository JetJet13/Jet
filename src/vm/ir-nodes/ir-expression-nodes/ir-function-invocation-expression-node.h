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
// Created by Johny Georges on 2024-11-08.
//

#ifndef JETLANG_IR_FUNCTION_INVOCATION_EXPRESSION_NODE_H
#define JETLANG_IR_FUNCTION_INVOCATION_EXPRESSION_NODE_H

#include <llvm/IR/Value.h>
#include "../../../core/ast/ast-nodes/ast-expression-nodes/ast-identifier-expression-node.h"
#include "ir-expression-node.h"
#include "../ir-instruction-node.h"
#include "../../ir-type/ir-function-type.h"
#include "../../../core/ast/ast-nodes/ast-expression-nodes/ast-function-invocation-expression-node.h"
#include "../ir-function-nodes/ir-function-argument-node.h"

class IRFunctionInvocationExpressionNode : public IRExpressionNode {
private:
    std::shared_ptr<ASTFunctionInvocationExpressionNode> _node;
    llvm::CallInst* _irCallInstruction;
    std::shared_ptr<IRInstructionNode> _irFunction;
    std::shared_ptr<IRType> _irFunctionType;
    std::vector<std::shared_ptr<IRFunctionArgumentNode>> _arguments;
    std::shared_ptr<IRType> _type;
    std::optional<std::shared_ptr<IRInstructionNode>> _varArgsTypeValueArgument;
public:
    IRFunctionInvocationExpressionNode(std::shared_ptr<ASTFunctionInvocationExpressionNode> node, std::shared_ptr<IRInstructionNode> irFunction, llvm::CallInst* irCallInstruction, std::shared_ptr<IRType> irFunctionType, std::vector<std::shared_ptr<IRFunctionArgumentNode>> arguments, std::shared_ptr<IRType> type, std::optional<std::shared_ptr<IRInstructionNode>> varArgsTypeValueArgument = {});
    void markAsGlobal() override;
    std::optional<std::shared_ptr<IRInstructionNode>> getVarArgsTypeValueArgument();
    std::vector<std::shared_ptr<IRFunctionArgumentNode>>* getIRArguments();
    std::shared_ptr<ASTFunctionInvocationExpressionNode> getNode();
    llvm::CallInst* getValue() override;
    std::shared_ptr<IRInstructionNode> getFunction();
    llvm::Value* getFunctionValue();
    std::shared_ptr<IRType> getFunctionIRType();
    std::shared_ptr<IRType> getIRType() override;
    std::shared_ptr<FunctionInvocationTypeSignature> getInvocationTypeSignature();
    std::shared_ptr<TypeSignature> getTypeSignature() override;
    std::shared_ptr<Position> getStartPosition() override;
    std::shared_ptr<Position> getEndPosition() override;
    IRNodeType getNodeType() override;
    std::string toString() override;
    void print(std::unique_ptr<llvm::raw_fd_ostream> *stream) override;
};

#endif //JETLANG_IR_FUNCTION_INVOCATION_EXPRESSION_NODE_H
