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

#include "ast-binary-comparator-expression-node.h"
#include "../../../../shared/utils/logger/logger.h"
#include "../../types/source-code-builder/source-code-builder.h"


ASTBinaryComparatorExpressionNode::ASTBinaryComparatorExpressionNode(std::shared_ptr<ASTExpressionNode> leftNode, std::shared_ptr<ASTBinaryComparatorOperatorNode> binaryOperator, std::shared_ptr<ASTExpressionNode> rightNode) {
    _leftNode = leftNode;
    _binaryOperator = binaryOperator;
    _rightNode = rightNode;
    _children.push_back(_leftNode);
    _children.push_back(_binaryOperator);
    _children.push_back(_rightNode);
}

std::shared_ptr<ASTExpressionNode> ASTBinaryComparatorExpressionNode::getLeftNode() {
    return _leftNode;
}

std::shared_ptr<ASTExpressionNode> ASTBinaryComparatorExpressionNode::getRightNode() {
    return _rightNode;
}

void ASTBinaryComparatorExpressionNode::setLeftTypeSignature(std::shared_ptr<TypeSignature> typeSignature) {
    _leftTypeSignature = typeSignature;
}

void ASTBinaryComparatorExpressionNode::setRightTypeSignature(std::shared_ptr<TypeSignature> typeSignature) {
    _rightTypeSignature = typeSignature;
}

std::shared_ptr<TypeSignature> ASTBinaryComparatorExpressionNode::getLeftTypeSignature() {
    return _leftTypeSignature;
}

std::shared_ptr<TypeSignature> ASTBinaryComparatorExpressionNode::getRightTypeSignature() {
    return _rightTypeSignature;
}

std::shared_ptr<ASTBinaryComparatorOperatorNode> ASTBinaryComparatorExpressionNode::getBinaryOperator() {
    return _binaryOperator;
}

std::shared_ptr<Position> ASTBinaryComparatorExpressionNode::getStartPosition() {
    return _leftNode->getStartPosition();
}

std::shared_ptr<Position> ASTBinaryComparatorExpressionNode::getEndPosition() {
    return _rightNode->getEndPosition();
}

ASTNodeType ASTBinaryComparatorExpressionNode::getNodeType() {
    return AST_BINARY_COMPARATOR_EXPRESSION_NODE;
}

std::string ASTBinaryComparatorExpressionNode::toString() {
    return "BINARY_COMPARATOR_EXPRESSION";
}

bool ASTBinaryComparatorExpressionNode::isSameAs(std::shared_ptr<ASTNode> other) {
    if (!other->is(this->getNodeType())) {
        return false;
    }
    auto otherNode = std::dynamic_pointer_cast<ASTBinaryComparatorExpressionNode>(other);
    return this->getBinaryOperator()->isSameAs(otherNode->getBinaryOperator()) &&
           this->getLeftNode()->isSameAs(otherNode->getLeftNode()) &&
           this->getRightNode()->isSameAs(otherNode->getRightNode());
}

void ASTBinaryComparatorExpressionNode::print() {
    Logger::log("----------", this->toString(), "----------");
    _leftNode->print();
    _binaryOperator->print();
    _rightNode->print();
    Logger::log("----------");
}

std::string ASTBinaryComparatorExpressionNode::toSourceCode() {
    auto sourceCodeBuilder = SourceCodeBuilder();
    sourceCodeBuilder.add(_leftNode)
            ->add(_binaryOperator)
            ->add(_rightNode);
    return sourceCodeBuilder.build();
}