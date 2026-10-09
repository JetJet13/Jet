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

#include "ast-literal-expression-node.h"
#include "../../../../shared/utils/logger/logger.h"

ASTLiteralExpressionNode::ASTLiteralExpressionNode(std::shared_ptr<ASTLiteralNode> literalNode) {
    _literalNode = literalNode;
    _children.push_back(_literalNode);
}

std::shared_ptr<ASTLiteralNode> ASTLiteralExpressionNode::getLiteralNode() {
    return _literalNode;
}

std::shared_ptr<Position> ASTLiteralExpressionNode::getStartPosition() {
    return _literalNode->getStartPosition();
}

std::shared_ptr<Position> ASTLiteralExpressionNode::getEndPosition() {
    return _literalNode->getEndPosition();
}

ASTNodeType ASTLiteralExpressionNode::getNodeType() {
    return AST_LITERAL_EXPRESSION_NODE;
}

std::string ASTLiteralExpressionNode::toString() {
    return "LITERAL_EXPRESSION";
}

bool ASTLiteralExpressionNode::isSameAs(std::shared_ptr<ASTNode> other) {
    if (!other->is(this->getNodeType())) {
        return false;
    }
    auto otherNode = std::dynamic_pointer_cast<ASTLiteralExpressionNode>(other);
    return this->getLiteralNode()->isSameAs(otherNode->getLiteralNode());
}

void ASTLiteralExpressionNode::print() {
    Logger::log(this->toString(), "-", _literalNode->toString());
}

std::string ASTLiteralExpressionNode::toSourceCode() {
    return _literalNode->toSourceCode();
}