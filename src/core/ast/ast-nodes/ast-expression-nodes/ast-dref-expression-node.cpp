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
// Created by Johny Georges on 2025-01-15.
//

#include "ast-dref-expression-node.h"
#include "../../../../shared/utils/logger/logger.h"
#include "../../types/source-code-builder/source-code-builder.h"


ASTDrefExpressionNode::ASTDrefExpressionNode(std::shared_ptr<ASTDrefNode> drefNode, std::shared_ptr<ASTExpressionNode> astExpressionNode) {
    _drefNode = drefNode;
    _expression = astExpressionNode;
    _children.push_back(_drefNode);
    _children.push_back(_expression);
}

std::shared_ptr<ASTExpressionNode> ASTDrefExpressionNode::getExpressionNode() {
    return _expression;
}

std::shared_ptr<ASTDrefNode> ASTDrefExpressionNode::getDrefNode() {
    return _drefNode;
}

std::shared_ptr<Position> ASTDrefExpressionNode::getStartPosition() {
    return _drefNode->getStartPosition();
}

std::shared_ptr<Position> ASTDrefExpressionNode::getEndPosition() {
    return _expression->getEndPosition();
}

ASTNodeType ASTDrefExpressionNode::getNodeType() {
    return AST_DREF_EXPRESSION_NODE;
}

std::string ASTDrefExpressionNode::toString() {
    return "DREF_EXPRESSION";
}

bool ASTDrefExpressionNode::isSameAs(std::shared_ptr<ASTNode> other) {
    if (!other->is(this->getNodeType())) {
        return false;
    }
    auto otherNode = std::dynamic_pointer_cast<ASTDrefExpressionNode>(other);
    return this->getExpressionNode()->isSameAs(otherNode->getExpressionNode());
}

void ASTDrefExpressionNode::print() {
    Logger::log("----------", this->toString(), "----------");
    _drefNode->print();
    _expression->print();
    Logger::log("----------");
}

std::string ASTDrefExpressionNode::toSourceCode() {
    auto sourceCodeBuilder = SourceCodeBuilder();
    sourceCodeBuilder.add(_drefNode)
    ->add(_expression);
    return sourceCodeBuilder.build();
}