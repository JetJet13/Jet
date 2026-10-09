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
// Created by Johny Georges on 2026-06-26.
//

#include "ast-object-access-shared-value-assignment-node.h"
#include "../../../../shared/utils/logger/logger.h"
#include "../../types/source-code-builder/source-code-builder.h"

ASTObjectAccessSharedValueAssignmentNode::ASTObjectAccessSharedValueAssignmentNode(std::shared_ptr<ASTObjectAccessExpressionNode> objectAccessExpression, std::shared_ptr<ASTSharedValueAssignmentOperatorNode> assignmentOperator) {
    _objectAccessExpression = objectAccessExpression;
    _assignmentOperator = assignmentOperator;
    _children.push_back(_objectAccessExpression);
    _children.push_back(_assignmentOperator);
}

std::shared_ptr<ASTObjectAccessExpressionNode> ASTObjectAccessSharedValueAssignmentNode::getObjectAccess() {
    return _objectAccessExpression;
}

std::shared_ptr<TypeSignature> ASTObjectAccessSharedValueAssignmentNode::getTypeSignature() {
    return _objectAccessExpression->getTypeSignature();
}

std::shared_ptr<Position> ASTObjectAccessSharedValueAssignmentNode::getStartPosition() {
    return _objectAccessExpression->getStartPosition();
}

std::shared_ptr<Position> ASTObjectAccessSharedValueAssignmentNode::getEndPosition() {
    return _assignmentOperator->getEndPosition();
}

ASTNodeType ASTObjectAccessSharedValueAssignmentNode::getNodeType() {
    return AST_OBJECT_ACCESS_SHARED_VALUE_ASSIGNMENT_NODE;
}

std::string ASTObjectAccessSharedValueAssignmentNode::toString() {
    return "OBJECT_ACCESS_SHARED_VALUE_ASSIGNMENT";
}

bool ASTObjectAccessSharedValueAssignmentNode::isSameAs(std::shared_ptr<ASTNode> other) {
    if (!other->is(this->getNodeType())) {
        return false;
    }
    auto otherNode = std::dynamic_pointer_cast<ASTObjectAccessSharedValueAssignmentNode>(other);
    return this->getObjectAccess()->isSameAs(otherNode->getObjectAccess());
}

void ASTObjectAccessSharedValueAssignmentNode::print() {
    Logger::log("----------", this->toString(), "----------");
    _objectAccessExpression->print();
    Logger::log("----------");
}

std::string ASTObjectAccessSharedValueAssignmentNode::toSourceCode() {
    auto sourceCodeBuilder = SourceCodeBuilder();
    sourceCodeBuilder.add(_objectAccessExpression)
            ->add(_assignmentOperator);
    return sourceCodeBuilder.build();
}