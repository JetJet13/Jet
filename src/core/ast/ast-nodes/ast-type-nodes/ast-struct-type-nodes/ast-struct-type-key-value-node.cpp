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
// Created by Johny Georges on 2025-06-28.
//

#include "ast-struct-type-key-value-node.h"
#include "../../../../../shared/utils/logger/logger.h"
#include "../../../types/source-code-builder/source-code-builder.h"

ASTStructTypeKeyValueNode::ASTStructTypeKeyValueNode(std::shared_ptr<ASTStructTypeKeyNode> name, std::shared_ptr<ASTStructTypeColonNode> colon, std::shared_ptr<ASTTypeNode> type) {
    _name = name;
    _colon = colon;
    _type = type;
    _children.push_back(_name);
    _children.push_back(_colon);
    _children.push_back(_type);
}

std::shared_ptr<ASTStructTypeKeyNode> ASTStructTypeKeyValueNode::getName() {
    return _name;
}

std::shared_ptr<ASTTypeNode> ASTStructTypeKeyValueNode::getType() {
    return _type;
}

void ASTStructTypeKeyValueNode::setTypeSignature(std::shared_ptr<TypeSignature> typeSignature) {
    _typeSignature = typeSignature;
}

std::shared_ptr<TypeSignature> ASTStructTypeKeyValueNode::getTypeSignature() {
    return _typeSignature;
}

std::shared_ptr<Position> ASTStructTypeKeyValueNode::getStartPosition() {
    return _name->getStartPosition();
}

std::shared_ptr<Position> ASTStructTypeKeyValueNode::getEndPosition() {
    return _type->getEndPosition();
}

ASTNodeType ASTStructTypeKeyValueNode::getNodeType() {
    return AST_STRUCT_TYPE_KEY_NODE;
}

std::string ASTStructTypeKeyValueNode::toString() {
    return "STRUCT_TYPE_KEY";
}

bool ASTStructTypeKeyValueNode::isSameAs(std::shared_ptr<ASTNode> other) {
    if (!other->is(this->getNodeType())){
        return false;
    }
    auto otherNode = std::dynamic_pointer_cast<ASTStructTypeKeyValueNode>(other);
    auto result = this->getName()->isSameAs(otherNode->getName()) &&
           this->getType()->isSameAs(otherNode->getType());
    return result;
}

void ASTStructTypeKeyValueNode::print() {
    Logger::log("----------", this->toString(), "----------");
    _name->print();
    _type->print();
    Logger::log("----------");
}

std::string ASTStructTypeKeyValueNode::toSourceCode() {
    auto sourceCodeBuilder = SourceCodeBuilder();
    sourceCodeBuilder.add(_name)
            ->add(_colon)
            ->add(_type);
    return sourceCodeBuilder.build();
}