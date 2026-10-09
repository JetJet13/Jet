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
// Created by Johny Georges on 2024-08-05.
//

#ifndef JETLANG_IR_STRING_LITERAL_EXPRESSION_NODE_H
#define JETLANG_IR_STRING_LITERAL_EXPRESSION_NODE_H

#include <llvm/IR/Value.h>
#include "../../../core/ast/ast-nodes/ast-expression-nodes/ast-literal-expression-node.h"
#include "../../ir-type/ir-pointer-type.h"
#include "../ir-literal-nodes/ir-string-literal-node.h"
#include "../../ir-type/ir-array-pointer-type.h"
#include "ir-expression-node.h"

class IRStringLiteralExpressionNode : public IRExpressionNode {
private:
    std::shared_ptr<ASTLiteralExpressionNode> _node;
    std::shared_ptr<IRStringLiteralNode> _irValue;
    std::shared_ptr<IRArrayPointerType> _irArrayPointerType;
    std::shared_ptr<IRInstructionNode> _sourceAllocation;
    std::shared_ptr<IRInstructionNode> _arrayPointerSourceAllocation;
public:
    IRStringLiteralExpressionNode(std::shared_ptr<ASTLiteralExpressionNode> node, std::shared_ptr<IRStringLiteralNode> irValue, std::shared_ptr<IRArrayPointerType> irArrayPointerType, std::shared_ptr<IRInstructionNode> sourceAllocation, std::shared_ptr<IRInstructionNode> arrayPointerSourceAllocation);
    std::shared_ptr<IRArrayPointerType> getIRArrayPointerType();
    std::shared_ptr<IRType> getIRType() override;
    std::shared_ptr<TypeSignature> getTypeSignature() override;
    std::shared_ptr<Position> getStartPosition() override;
    std::shared_ptr<Position> getEndPosition() override;
    llvm::Constant* getValue() override;
    std::optional<std::shared_ptr<IRInstructionNode>> getSourceAllocation() override;
    std::shared_ptr<IRInstructionNode> getSourceAggregateAllocation();
    std::shared_ptr<IRInstructionNode> getAggregatePointerAllocation();
    IRNodeType getNodeType() override;
    std::string toString() override;
    void print(std::unique_ptr<llvm::raw_fd_ostream> *stream) override;
};

#endif //JETLANG_IR_STRING_LITERAL_EXPRESSION_NODE_H
