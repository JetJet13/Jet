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
// Created by Johny Georges on 2024-03-26.
//

#include "ast-object-access-source-node.h"
#include "../../../../shared/utils/logger/logger.h"

ASTObjectAccessSourceNode::ASTObjectAccessSourceNode(std::shared_ptr<ASTExpressionNode> source) {
    _source = source;
    _children.push_back(_source);
}

std::shared_ptr<ASTExpressionNode> ASTObjectAccessSourceNode::getSource() {
    return _source;
}

std::shared_ptr<Position> ASTObjectAccessSourceNode::getStartPosition() {
    return _source->getStartPosition();
}

std::shared_ptr<Position> ASTObjectAccessSourceNode::getEndPosition() {
    return _source->getEndPosition();
}

ASTNodeType ASTObjectAccessSourceNode::getNodeType() {
    return AST_OBJECT_ACCESS_SOURCE_NODE;
}

std::string ASTObjectAccessSourceNode::toString() {
    return "OBJECT_ACCESS_SOURCE";
}

bool ASTObjectAccessSourceNode::isSameAs(std::shared_ptr<ASTNode> other) {
    if (!other->is(this->getNodeType())) {
        return false;
    }
    auto otherNode = std::dynamic_pointer_cast<ASTObjectAccessSourceNode>(other);
    return this->getSource()->isSameAs(otherNode->getSource());
}

void ASTObjectAccessSourceNode::print() {
    Logger::log("----------", this->toString(), "----------");
    _source->print();
    Logger::log("----------");
}

std::string ASTObjectAccessSourceNode::toSourceCode() {
    return _source->toSourceCode();
}