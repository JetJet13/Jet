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
// Created by Johny Georges on 2024-03-29.
//

#include "ast-for-in-source-node.h"
#include "../../../../shared/utils/logger/logger.h"

ASTForInSourceNode::ASTForInSourceNode(std::shared_ptr<ASTExpressionNode> source) {
    _source = source;
    _children.push_back(_source);
}

std::shared_ptr<ASTExpressionNode> ASTForInSourceNode::getSource() {
    return _source;
}

void ASTForInSourceNode::setTypeSignature(std::shared_ptr<TypeSignature> typeSignature) {
    _typeSignature = typeSignature;
}

std::shared_ptr<TypeSignature> ASTForInSourceNode::getTypeSignature() {
    return _typeSignature;
}

std::shared_ptr<Position> ASTForInSourceNode::getStartPosition() {
    return _source->getStartPosition();
}

std::shared_ptr<Position> ASTForInSourceNode::getEndPosition() {
    return _source->getEndPosition();
}

ASTNodeType ASTForInSourceNode::getNodeType() {
    return AST_FOR_IN_SOURCE_NODE;
}

std::string ASTForInSourceNode::toString() {
    return "FOR_IN_SOURCE";
}

bool ASTForInSourceNode::isSameAs(std::shared_ptr<ASTNode> other) {
    if (!other->is(this->getNodeType())) {
        return false;
    }
    auto otherNode = std::dynamic_pointer_cast<ASTForInSourceNode>(other);
    return this->getSource()->isSameAs(otherNode->getSource());
}

void ASTForInSourceNode::print() {
    Logger::log("----------", this->toString(), "----------");
    _source->print();
    Logger::log("----------");
}

std::string ASTForInSourceNode::toSourceCode() {
    return _source->toSourceCode();
}