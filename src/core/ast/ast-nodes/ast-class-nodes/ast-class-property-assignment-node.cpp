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
// Created by Johny Georges on 2024-04-24.
//

#include "ast-class-property-assignment-node.h"
#include "../../../../shared/utils/logger/logger.h"
#include "../../types/source-code-builder/source-code-builder.h"
#include "ast-class-property-access-node.h"

ASTClassPropertyAssignmentNode::ASTClassPropertyAssignmentNode(std::shared_ptr<ASTClassPropertyAccessNode> classPropertyAccess, std::shared_ptr<ASTAssignmentOperatorNode> assignmentOperator) {
    _classPropertyAccess = classPropertyAccess;
    _assignmentOperator = assignmentOperator;
    _children.push_back(_classPropertyAccess);
    _children.push_back(_assignmentOperator);
}

std::shared_ptr<ASTClassAccessNode> ASTClassPropertyAssignmentNode::getClassAccess() {
    return _classPropertyAccess->getClassAccess();
}

std::shared_ptr<ASTClassPropertyNameNode> ASTClassPropertyAssignmentNode::getProperty() {
    return _classPropertyAccess->getPropertyName();
}

void ASTClassPropertyAssignmentNode::setTypeSignature(std::shared_ptr<TypeSignature> typeSignature) {
    _typeSignature = typeSignature;
}

std::shared_ptr<TypeSignature> ASTClassPropertyAssignmentNode::getTypeSignature() {
    return _typeSignature;
}

std::shared_ptr<Position> ASTClassPropertyAssignmentNode::getStartPosition() {
    return _classPropertyAccess->getStartPosition();
}

std::shared_ptr<Position> ASTClassPropertyAssignmentNode::getEndPosition() {
    return _assignmentOperator->getEndPosition();
}

ASTNodeType ASTClassPropertyAssignmentNode::getNodeType() {
    return AST_CLASS_PROPERTY_ASSIGNMENT_NODE;
}

std::string ASTClassPropertyAssignmentNode::toString() {
    return "CLASS_PROPERTY_ASSIGNMENT";
}

bool ASTClassPropertyAssignmentNode::isSameAs(std::shared_ptr<ASTNode> other) {
    if (!other->is(this->getNodeType())){
        return false;
    }
    auto otherNode = std::dynamic_pointer_cast<ASTClassPropertyAssignmentNode>(other);
    return this->getProperty()->isSameAs(otherNode->getProperty());
}

void ASTClassPropertyAssignmentNode::print() {
    Logger::log("----------", this->toString(), "----------");
    _classPropertyAccess->print();
    Logger::log("----------");
}

std::string ASTClassPropertyAssignmentNode::toSourceCode() {
    auto sourceCodeBuilder = SourceCodeBuilder();
    sourceCodeBuilder.add(_classPropertyAccess)
    ->add(_assignmentOperator);
    return sourceCodeBuilder.build();
}