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

#include "ast-array-access-shared-value-assignment-node.h"
#include "../../../../shared/utils/logger/logger.h"
#include "../../types/source-code-builder/source-code-builder.h"

ASTArrayAccessSharedValueAssignmentNode::ASTArrayAccessSharedValueAssignmentNode(std::shared_ptr<ASTArrayAccessExpressionNode> arrayAccessExpression, std::shared_ptr<ASTSharedValueAssignmentOperatorNode> assignmentOperator) {
    _arrayAccessExpression = arrayAccessExpression;
    _assignmentOperator = assignmentOperator;
    _children.push_back(_arrayAccessExpression);
    _children.push_back(_assignmentOperator);
}

std::shared_ptr<ASTArrayAccessExpressionNode> ASTArrayAccessSharedValueAssignmentNode::getArrayAccess() {
    return _arrayAccessExpression;
}

std::shared_ptr<TypeSignature> ASTArrayAccessSharedValueAssignmentNode::getTypeSignature() {
    return _arrayAccessExpression->getTypeSignature();
}

std::shared_ptr<Position> ASTArrayAccessSharedValueAssignmentNode::getStartPosition() {
    return _arrayAccessExpression->getStartPosition();
}

std::shared_ptr<Position> ASTArrayAccessSharedValueAssignmentNode::getEndPosition() {
    return _assignmentOperator->getEndPosition();
}

ASTNodeType ASTArrayAccessSharedValueAssignmentNode::getNodeType() {
    return AST_ARRAY_ACCESS_SHARED_VALUE_ASSIGNMENT_NODE;
}

std::string ASTArrayAccessSharedValueAssignmentNode::toString() {
    return "ARRAY_ACCESS_SHARED_VALUE_ASSIGNMENT";
}

bool ASTArrayAccessSharedValueAssignmentNode::isSameAs(std::shared_ptr<ASTNode> other) {
    if (!other->is(this->getNodeType())) {
        return false;
    }
    auto otherNode = std::dynamic_pointer_cast<ASTArrayAccessSharedValueAssignmentNode>(other);
    return this->getArrayAccess()->isSameAs(otherNode->getArrayAccess());
}

void ASTArrayAccessSharedValueAssignmentNode::print() {
    Logger::log("----------", this->toString(), "----------");
    _arrayAccessExpression->print();
    Logger::log("----------");
}

std::string ASTArrayAccessSharedValueAssignmentNode::toSourceCode() {
    auto sourceCodeBuilder = SourceCodeBuilder();
    sourceCodeBuilder.add(_arrayAccessExpression)
            ->add(_assignmentOperator);
    return sourceCodeBuilder.build();
}