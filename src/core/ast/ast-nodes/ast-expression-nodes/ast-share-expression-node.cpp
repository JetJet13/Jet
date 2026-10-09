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
// Created by Johny Georges on 2026-07-11.
//

#include "ast-share-expression-node.h"
#include "../../../../shared/utils/logger/logger.h"
#include "../../types/source-code-builder/source-code-builder.h"


ASTShareExpressionNode::ASTShareExpressionNode(std::shared_ptr<ASTShareNode> shareNode, std::shared_ptr<ASTExpressionNode> astExpressionNode) {
    _shareNode = shareNode;
    _expression = astExpressionNode;
    _children.push_back(_shareNode);
    _children.push_back(_expression);
}

std::shared_ptr<ASTExpressionNode> ASTShareExpressionNode::getExpressionNode() {
    return _expression;
}

std::shared_ptr<ASTShareNode> ASTShareExpressionNode::getShareNode() {
    return _shareNode;
}

std::shared_ptr<TypeSignature> ASTShareExpressionNode::getTypeSignature() {
    return _typeSignature;
}

std::shared_ptr<SharedTypeSignature> ASTShareExpressionNode::getSharedTypeSignature() {
    return std::dynamic_pointer_cast<SharedTypeSignature>(_typeSignature);
}

void ASTShareExpressionNode::setTypeSignature(std::shared_ptr<SharedTypeSignature> typeSignature) {
    _typeSignature = typeSignature;
}

std::shared_ptr<Position> ASTShareExpressionNode::getStartPosition() {
    return _shareNode->getStartPosition();
}

std::shared_ptr<Position> ASTShareExpressionNode::getEndPosition() {
    return _expression->getEndPosition();
}

ASTNodeType ASTShareExpressionNode::getNodeType() {
    return AST_SHARE_EXPRESSION_NODE;
}

std::string ASTShareExpressionNode::toString() {
    return "SHARE_EXPRESSION";
}

bool ASTShareExpressionNode::isSameAs(std::shared_ptr<ASTNode> other) {
    if (!other->is(this->getNodeType())) {
        return false;
    }
    auto otherNode = std::dynamic_pointer_cast<ASTShareExpressionNode>(other);
    return this->getExpressionNode()->isSameAs(otherNode->getExpressionNode());
}

void ASTShareExpressionNode::print() {
    Logger::log("----------", this->toString(), "----------");
    _shareNode->print();
    _expression->print();
    Logger::log("----------");
}

std::string ASTShareExpressionNode::toSourceCode() {
    auto sourceCodeBuilder = SourceCodeBuilder();
    sourceCodeBuilder.add(_shareNode)
            ->add(_expression);
    return sourceCodeBuilder.build();
}