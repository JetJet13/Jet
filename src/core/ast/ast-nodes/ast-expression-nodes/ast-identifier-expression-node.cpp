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
// Created by Johny Georges on 2024-02-17.
//

#include "ast-identifier-expression-node.h"
#include "../../../../shared/utils/logger/logger.h"

ASTIdentifierExpressionNode::ASTIdentifierExpressionNode(std::shared_ptr<ASTIdentifierNode> identifierNode) {
    _identifierNode = identifierNode;
    _children.push_back(_identifierNode);
}

std::shared_ptr<ASTIdentifierNode> ASTIdentifierExpressionNode::getIdentifierNode() {
    return _identifierNode;
}

std::shared_ptr<Position> ASTIdentifierExpressionNode::getStartPosition() {
    return _identifierNode->getStartPosition();
}

std::shared_ptr<Position> ASTIdentifierExpressionNode::getEndPosition() {
    return _identifierNode->getEndPosition();
}

ASTNodeType ASTIdentifierExpressionNode::getNodeType() {
    return AST_IDENTIFIER_EXPRESSION_NODE;
}

std::string ASTIdentifierExpressionNode::toString() {
    return "IDENTIFIER_EXPRESSION";
}

bool ASTIdentifierExpressionNode::isSameAs(std::shared_ptr<ASTNode> other) {
    if (!other->is(this->getNodeType())) {
        return false;
    }
    auto otherNode = std::dynamic_pointer_cast<ASTIdentifierExpressionNode>(other);
    return this->getIdentifierNode()->isSameAs(otherNode->getIdentifierNode());
}

void ASTIdentifierExpressionNode::print() {
    Logger::log(this->toString(), "-", _identifierNode->toString());
}

std::string ASTIdentifierExpressionNode::toSourceCode() {
    return _identifierNode->toSourceCode();
}