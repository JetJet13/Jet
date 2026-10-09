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
// Created by Johny Georges on 2024-06-29.
//

#ifndef JETLANG_IR_BINARY_COMPARISON_EXPRESSION_NODE_H
#define JETLANG_IR_BINARY_COMPARISON_EXPRESSION_NODE_H

#include <llvm/IR/InstrTypes.h>
#include "ir-binary-expression-node.h"
#include "../../../../core/ast/ast-nodes/ast-expression-nodes/ast-binary-comparator-expression-node.h"

class IRBinaryComparisonExpressionNode : public IRBinaryExpressionNode {
private:
    std::shared_ptr<ASTBinaryComparatorExpressionNode> _node;
    llvm::CmpInst* _irValue;
    std::shared_ptr<IRExpressionNode> _irLeftNode;
    std::shared_ptr<IRExpressionNode> _irRightNode;
    std::shared_ptr<IRType> _type;
    std::shared_ptr<IRType> _leftIrType;
    std::shared_ptr<IRType> _rightIrType;
public:
    IRBinaryComparisonExpressionNode(std::shared_ptr<ASTBinaryComparatorExpressionNode> astNode, llvm::CmpInst* irValue, std::shared_ptr<IRExpressionNode> irLeftNode, std::shared_ptr<IRExpressionNode> irRightNode, std::shared_ptr<IRType> type, std::shared_ptr<IRType> leftIrType, std::shared_ptr<IRType> rightIrType);
    void markAsGlobal() override;
    llvm::CmpInst* getValue() override;
    bool isPredicateEqual();
    bool isPredicateNotEqual();
    std::shared_ptr<IRType> getLeftIrType();
    std::shared_ptr<IRType> getRightIrType();
    std::shared_ptr<IRExpressionNode> getLeftNode();
    std::shared_ptr<IRExpressionNode> getRightNode();
    std::shared_ptr<IRType> getIRType() override;
    std::shared_ptr<TypeSignature> getTypeSignature() override;
    std::shared_ptr<Position> getStartPosition() override;
    std::shared_ptr<Position> getEndPosition() override;
    IRNodeType getNodeType() override;
    std::string toString() override;
    void print(std::unique_ptr<llvm::raw_fd_ostream> *stream) override;
};

#endif //JETLANG_IR_BINARY_COMPARISON_EXPRESSION_NODE_H
