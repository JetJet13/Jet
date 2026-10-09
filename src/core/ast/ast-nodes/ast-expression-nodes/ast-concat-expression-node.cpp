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
// Created by Johny Georges on 2025-06-07.
//

#include "ast-concat-expression-node.h"
#include "../../../../shared/utils/logger/logger.h"
#include "../../types/source-code-builder/source-code-builder.h"


ASTConcatExpressionNode::ASTConcatExpressionNode(std::shared_ptr<ASTExpressionNode> leftNode, std::shared_ptr<ASTConcatNode> concatNode, std::shared_ptr<ASTExpressionNode> rightNode) {
    _leftNode = leftNode;
    _concatNode = concatNode;
    _rightNode = rightNode;
    _children.push_back(_leftNode);
    _children.push_back(_concatNode);
    _children.push_back(_rightNode);
}

std::shared_ptr<ASTExpressionNode> ASTConcatExpressionNode::getLeftNode() {
    return _leftNode;
}

std::shared_ptr<ASTExpressionNode> ASTConcatExpressionNode::getRightNode() {
    return _rightNode;
}

std::shared_ptr<ASTConcatNode> ASTConcatExpressionNode::getConcatNode() {
    return _concatNode;
}

std::shared_ptr<Position> ASTConcatExpressionNode::getStartPosition() {
    return _leftNode->getStartPosition();
}

std::shared_ptr<Position> ASTConcatExpressionNode::getEndPosition() {
    return _rightNode->getEndPosition();
}

ASTNodeType ASTConcatExpressionNode::getNodeType() {
    return AST_CONCAT_EXPRESSION_NODE;
}

std::string ASTConcatExpressionNode::toString() {
    return "CONCAT_EXPRESSION";
}

bool ASTConcatExpressionNode::isSameAs(std::shared_ptr<ASTNode> other) {
    if (!other->is(this->getNodeType())) {
        return false;
    }
    auto otherNode = std::dynamic_pointer_cast<ASTConcatExpressionNode>(other);
    return this->getLeftNode()->isSameAs(otherNode->getLeftNode()) &&
           this->getRightNode()->isSameAs(otherNode->getRightNode());
}

void ASTConcatExpressionNode::print() {
    Logger::log("----------", this->toString(), "----------");
    _leftNode->print();
    _concatNode->print();
    _rightNode->print();
    Logger::log("----------");
}

std::string ASTConcatExpressionNode::toSourceCode() {
    auto sourceCodeBuilder = SourceCodeBuilder();
    sourceCodeBuilder.add(_leftNode)
            ->add(_concatNode)
            ->add(_rightNode);
    return sourceCodeBuilder.build();
}