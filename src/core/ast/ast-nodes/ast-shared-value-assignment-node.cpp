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
// Created by Johny Georges on 2026-02-16.
//

#include "ast-shared-value-assignment-node.h"
#include "../../../shared/utils/logger/logger.h"
#include "../types/source-code-builder/source-code-builder.h"

ASTSharedValueAssignmentNode::ASTSharedValueAssignmentNode(std::shared_ptr<ASTIdentifierNode> astIdentifierNode, std::shared_ptr<ASTSharedValueAssignmentOperatorNode> assignmentOperator) {
    _identifier = astIdentifierNode;
    _assignmentOperator = assignmentOperator;
    _children.push_back(_identifier);
    _children.push_back(_assignmentOperator);
}

std::shared_ptr<ASTIdentifierNode> ASTSharedValueAssignmentNode::getIdentifierNode() {
    return _identifier;
}

void ASTSharedValueAssignmentNode::setTypeSignature(std::shared_ptr<TypeSignature> typeSignature) {
    _typeSignature = typeSignature;
}

std::shared_ptr<TypeSignature> ASTSharedValueAssignmentNode::getTypeSignature() {
    return _typeSignature;
}

std::shared_ptr<Position> ASTSharedValueAssignmentNode::getStartPosition() {
    return _identifier->getStartPosition();
}

std::shared_ptr<Position> ASTSharedValueAssignmentNode::getEndPosition() {
    return _assignmentOperator->getEndPosition();
}

ASTNodeType ASTSharedValueAssignmentNode::getNodeType() {
    return AST_SHARED_VALUE_ASSIGNMENT_NODE;
}

std::string ASTSharedValueAssignmentNode::toString() {
    return "SHARED_VALUE_ASSIGNMENT";
}

bool ASTSharedValueAssignmentNode::isSameAs(std::shared_ptr<ASTNode> other) {
    if (!other->is(this->getNodeType())) {
        return false;
    }
    auto otherNode = std::dynamic_pointer_cast<ASTSharedValueAssignmentNode>(other);
    return this->getIdentifierNode()->isSameAs(otherNode->getIdentifierNode());
}

void ASTSharedValueAssignmentNode::print() {
    Logger::log("----------", this->toString(), "----------");
    _identifier->print();
    Logger::log("----------");
}

std::string ASTSharedValueAssignmentNode::toSourceCode() {
    auto sourceCodeBuilder = SourceCodeBuilder();
    sourceCodeBuilder.add(_identifier)
            ->add(_assignmentOperator);
    return sourceCodeBuilder.build();
}