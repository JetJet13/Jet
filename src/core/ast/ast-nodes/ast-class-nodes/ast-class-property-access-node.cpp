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

#include "ast-class-property-access-node.h"
#include "../../../../shared/utils/logger/logger.h"
#include "../../types/source-code-builder/source-code-builder.h"

ASTClassPropertyAccessNode::ASTClassPropertyAccessNode(std::shared_ptr<ASTClassAccessNode> classAccess, std::shared_ptr<ASTClassPropertyNameNode> property) {
    _classAccess = classAccess;
    _property = property;
    _children.push_back(_classAccess);
    _children.push_back(_property);
}

std::shared_ptr<ASTClassAccessNode> ASTClassPropertyAccessNode::getClassAccess() {
    return _classAccess;
}

std::shared_ptr<ASTClassPropertyNameNode> ASTClassPropertyAccessNode::getPropertyName() {
    return _property;
}

std::shared_ptr<Position> ASTClassPropertyAccessNode::getStartPosition() {
    return _classAccess->getStartPosition();
}

std::shared_ptr<Position> ASTClassPropertyAccessNode::getEndPosition() {
    return _property->getEndPosition();
}

ASTNodeType ASTClassPropertyAccessNode::getNodeType() {
    return AST_CLASS_PROPERTY_ACCESS_NODE;
}

std::string ASTClassPropertyAccessNode::toString() {
    return "CLASS_PROPERTY_ACCESS";
}

bool ASTClassPropertyAccessNode::isSameAs(std::shared_ptr<ASTNode> other) {
    if (!other->is(this->getNodeType())){
        return false;
    }
    auto otherNode = std::dynamic_pointer_cast<ASTClassPropertyAccessNode>(other);
    return this->getPropertyName()->isSameAs(otherNode->getPropertyName());
}

void ASTClassPropertyAccessNode::print() {
    Logger::log("----------", this->toString(), "----------");
    _property->print();
    Logger::log("----------");
}

std::string ASTClassPropertyAccessNode::toSourceCode() {
    auto sourceCodeBuilder = SourceCodeBuilder();
    sourceCodeBuilder.add(_classAccess)
    ->add(_property);
    return sourceCodeBuilder.build();
}