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
// Created by Johny Georges on 2026-03-02.
//

#ifndef JETLANG_AST_BINARY_COMPARATOR_EXPRESSION_NODE_H
#define JETLANG_AST_BINARY_COMPARATOR_EXPRESSION_NODE_H

#include "ast-expression-node.h"
#include "../ast-operator-nodes/ast-binary-operators/ast-binary-comparator-operator-node.h"

class ASTBinaryComparatorExpressionNode : public ASTExpressionNode {
private:
    std::shared_ptr<ASTExpressionNode> _leftNode;
    std::shared_ptr<ASTExpressionNode> _rightNode;
    std::shared_ptr<ASTBinaryComparatorOperatorNode> _binaryOperator;
    std::shared_ptr<TypeSignature> _leftTypeSignature = std::make_shared<UnknownTypeSignature>();
    std::shared_ptr<TypeSignature> _rightTypeSignature = std::make_shared<UnknownTypeSignature>();
public:
    ASTBinaryComparatorExpressionNode(std::shared_ptr<ASTExpressionNode> leftNode, std::shared_ptr<ASTBinaryComparatorOperatorNode> binaryOperator, std::shared_ptr<ASTExpressionNode> rightNode);
    std::shared_ptr<ASTExpressionNode> getLeftNode();
    std::shared_ptr<ASTExpressionNode> getRightNode();
    void setLeftTypeSignature(std::shared_ptr<TypeSignature> typeSignature);
    void setRightTypeSignature(std::shared_ptr<TypeSignature> typeSignature);
    std::shared_ptr<TypeSignature> getLeftTypeSignature();
    std::shared_ptr<TypeSignature> getRightTypeSignature();
    std::shared_ptr<ASTBinaryComparatorOperatorNode> getBinaryOperator();
    std::shared_ptr<Position> getStartPosition() override;
    std::shared_ptr<Position> getEndPosition() override;
    ASTNodeType getNodeType() override;
    std::string toString() override;
    bool isSameAs(std::shared_ptr<ASTNode> other) override;
    void print() override;
    std::string toSourceCode() override;
};

#endif //JETLANG_AST_BINARY_COMPARATOR_EXPRESSION_NODE_H
