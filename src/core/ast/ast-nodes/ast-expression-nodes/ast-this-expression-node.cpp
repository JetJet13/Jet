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
// Created by Johny Georges on 2024-04-20.
//

#include "ast-this-expression-node.h"
#include "../../../../shared/utils/logger/logger.h"


ASTThisExpressionNode::ASTThisExpressionNode(std::shared_ptr<ASTThisNode> thisNode) {
    _this = thisNode;
    _children.push_back(_this);
}

std::shared_ptr<ASTThisNode> ASTThisExpressionNode::getThisNode() {
    return _this;
}

std::shared_ptr<Position> ASTThisExpressionNode::getStartPosition() {
    return _this->getStartPosition();
}

std::shared_ptr<Position> ASTThisExpressionNode::getEndPosition() {
    return _this->getEndPosition();
}

ASTNodeType ASTThisExpressionNode::getNodeType() {
    return AST_THIS_EXPRESSION_NODE;
}

std::string ASTThisExpressionNode::toString() {
    return "THIS_EXPRESSION";
}

bool ASTThisExpressionNode::isSameAs(std::shared_ptr<ASTNode> other) {
    if (!other->is(this->getNodeType())) {
        return false;
    }
    auto otherNode = std::dynamic_pointer_cast<ASTThisExpressionNode>(other);
    return this->getThisNode()->isSameAs(otherNode->getThisNode());
}

void ASTThisExpressionNode::print() {
    Logger::log("----------", this->toString(), "----------");
    _this->print();
    Logger::log("----------");
}

std::string ASTThisExpressionNode::toSourceCode() {
    return _this->toSourceCode();
}