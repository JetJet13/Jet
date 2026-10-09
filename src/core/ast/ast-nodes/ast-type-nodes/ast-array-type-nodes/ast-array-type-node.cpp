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
// Created by Johny Georges on 2024-04-09.
//

#include "ast-array-type-node.h"
#include "../../../../../shared/utils/logger/logger.h"
#include "../../../types/source-code-builder/source-code-builder.h"

ASTArrayTypeNode::ASTArrayTypeNode(std::shared_ptr<ASTArrayTypeStartNode> arrayStart, std::shared_ptr<ASTTypeNode> elementType, std::shared_ptr<ASTArrayTypeEndNode> arrayEnd) {
    _arrayStart = arrayStart;
    _elementType = elementType;
    _arrayEnd = arrayEnd;
    _children.push_back(_arrayStart);
    _children.push_back(_elementType);
    _children.push_back(_arrayEnd);
}

std::shared_ptr<ASTTypeNode> ASTArrayTypeNode::getElementType() {
    return _elementType;
}

std::shared_ptr<Position> ASTArrayTypeNode::getStartPosition() {
    return _arrayStart->getStartPosition();
}

std::shared_ptr<Position> ASTArrayTypeNode::getEndPosition() {
    return _arrayEnd->getEndPosition();
}

ASTNodeType ASTArrayTypeNode::getNodeType() {
    return AST_ARRAY_TYPE_NODE;
}

std::string ASTArrayTypeNode::toString() {
    return "ARRAY_TYPE";
}

bool ASTArrayTypeNode::isSameAs(std::shared_ptr<ASTNode> other) {
    if (!other->is(this->getNodeType())){
        return false;
    }

    auto otherNode = std::dynamic_pointer_cast<ASTArrayTypeNode>(other);
    return this->getElementType()->isSameAs(otherNode->getElementType());
}

void ASTArrayTypeNode::print() {
    Logger::log("----------", this->toString(), "----------");
    _elementType->print();
    Logger::log("----------");
}

std::string ASTArrayTypeNode::toSourceCode() {
    auto sourceCodeBuilder = SourceCodeBuilder();
    sourceCodeBuilder.add(_arrayStart)->add(_elementType)->add(_arrayEnd);
    return sourceCodeBuilder.build();
}