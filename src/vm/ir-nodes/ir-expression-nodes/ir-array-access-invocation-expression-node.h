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
// Created by Johny Georges on 2026-02-06.
//

#ifndef JETLANG_IR_ARRAY_ACCESS_INVOCATION_EXPRESSION_NODE_H
#define JETLANG_IR_ARRAY_ACCESS_INVOCATION_EXPRESSION_NODE_H

#include <llvm/IR/Value.h>
#include "ir-expression-node.h"
#include "../ir-instruction-node.h"
#include "../../ir-type/ir-function-type.h"
#include "../../../core/ast/ast-nodes/ast-expression-nodes/ast-array-access-invocation-expression-node.h"
#include "ir-array-access-expression-node.h"
#include "../ir-function-nodes/ir-function-argument-node.h"

class IRArrayAccessInvocationExpressionNode : public IRExpressionNode {
private:
    std::shared_ptr<ASTArrayAccessInvocationExpressionNode> _node;
    std::shared_ptr<IRArrayAccessExpressionNode> _irArrayAccessExpression;
    llvm::CallInst* _irCallInstruction;
    std::shared_ptr<IRType> _irFunctionType;
    std::vector<std::shared_ptr<IRFunctionArgumentNode>> _arguments;
    std::shared_ptr<IRType> _type;
public:
    IRArrayAccessInvocationExpressionNode(std::shared_ptr<ASTArrayAccessInvocationExpressionNode> node, std::shared_ptr<IRArrayAccessExpressionNode> irArrayAccessExpression, llvm::CallInst* irCallInstruction, std::shared_ptr<IRType> irFunctionType, std::vector<std::shared_ptr<IRFunctionArgumentNode>> arguments, std::shared_ptr<IRType> type);
    void markAsGlobal() override;
    std::shared_ptr<IRArrayAccessExpressionNode> getIRArrayAccessExpression();
    std::vector<std::shared_ptr<IRFunctionArgumentNode>>* getIRArguments();
    llvm::CallInst* getValue() override;
    std::shared_ptr<IRType> getFunctionIRType();
    std::shared_ptr<IRType> getIRType() override;
    std::shared_ptr<TypeSignature> getTypeSignature() override;
    std::shared_ptr<Position> getStartPosition() override;
    std::shared_ptr<Position> getEndPosition() override;
    IRNodeType getNodeType() override;
    std::string toString() override;
    void print(std::unique_ptr<llvm::raw_fd_ostream> *stream) override;
};

#endif //JETLANG_IR_ARRAY_ACCESS_INVOCATION_EXPRESSION_NODE_H
