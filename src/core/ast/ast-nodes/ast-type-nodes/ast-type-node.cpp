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
// Created by Johny Georges on 2024-03-19.
//

#include "ast-type-node.h"
#include "../../../../shared/utils/logger/logger.h"
#include "../../types/source-code-builder/source-code-builder.h"

ASTTypeNode::ASTTypeNode(std::shared_ptr<ASTTypeBaseNode> type) {
    _type = type;
    _children.push_back(_type);
}

std::shared_ptr<ASTTypeBaseNode> ASTTypeNode::getType() {
    return _type;
}

void ASTTypeNode::setTypeSignature(std::shared_ptr<TypeSignature> typeSignature) {
    _type->setTypeSignature(typeSignature);
}

std::shared_ptr<TypeSignature> ASTTypeNode::getTypeSignature() {
    return _type->getTypeSignature();
}

std::shared_ptr<Position> ASTTypeNode::getStartPosition() {
    return _type->getStartPosition();
}

std::shared_ptr<Position> ASTTypeNode::getEndPosition() {
    return _type->getEndPosition();
}

ASTNodeType ASTTypeNode::getNodeType() {
    return AST_TYPE_NODE;
}

std::string ASTTypeNode::toString() {
    return "TYPE";
}

bool ASTTypeNode::isSameAs(std::shared_ptr<ASTNode> other) {
    if (!other->is(this->getNodeType())){
        return false;
    }
    auto otherNode = std::dynamic_pointer_cast<ASTTypeNode>(other);
    return _type->isSameAs(otherNode->getType());
}

void ASTTypeNode::print() {
    Logger::log("----------", this->toString(), "----------");
    _type->print();
    Logger::log("----------");
}

std::string ASTTypeNode::toSourceCode() {
    return _type->toSourceCode();
}