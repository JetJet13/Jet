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
// Created by Johny Georges on 2024-07-06.
//

#ifndef JETLANG_IR_ARRAY_ACCESS_EXPRESSION_NODE_H
#define JETLANG_IR_ARRAY_ACCESS_EXPRESSION_NODE_H

#include <llvm/IR/Value.h>
#include <llvm/IR/Constants.h>
#include "../../../core/ast/ast-nodes/ast-expression-nodes/ast-array-access-expression-node.h"
#include "ir-expression-node.h"

class IRArrayAccessExpressionNode : public IRExpressionNode {
protected:
    std::shared_ptr<ASTArrayAccessExpressionNode> _node;
    std::shared_ptr<IRExpressionNode> _irSource;
    std::shared_ptr<IRExpressionNode> _irIndex;
    std::shared_ptr<IRType> _type;
    std::optional<std::shared_ptr<IRInstructionNode>> _sourceAllocation;
public:
    IRArrayAccessExpressionNode(std::shared_ptr<ASTArrayAccessExpressionNode> node, std::shared_ptr<IRExpressionNode> irSource, std::shared_ptr<IRExpressionNode> irIndex, std::shared_ptr<IRType> type, std::optional<std::shared_ptr<IRInstructionNode>> sourceAllocation);
    void markAsGlobal() override;
    std::shared_ptr<IRExpressionNode> getSourceExpression();
    std::shared_ptr<IRExpressionNode> getIndexExpression();
    std::shared_ptr<ASTArrayAccessExpressionNode> getNode();
    std::optional<std::shared_ptr<IRInstructionNode>> getSourceAllocation() override;
    llvm::Value* getValue() override;
    std::shared_ptr<IRType> getIRType() override;
    std::shared_ptr<TypeSignature> getTypeSignature() override;
    std::shared_ptr<Position> getStartPosition() override;
    std::shared_ptr<Position> getEndPosition() override;
    IRNodeType getNodeType() override;
    std::string toString() override;
    void print(std::unique_ptr<llvm::raw_fd_ostream> *stream) override;
};

#endif //JETLANG_IR_ARRAY_ACCESS_EXPRESSION_NODE_H
