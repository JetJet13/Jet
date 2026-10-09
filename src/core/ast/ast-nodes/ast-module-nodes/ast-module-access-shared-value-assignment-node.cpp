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

#include "ast-module-access-shared-value-assignment-node.h"
#include "../../../../shared/utils/logger/logger.h"
#include "../../types/source-code-builder/source-code-builder.h"

ASTModuleAccessSharedValueAssignmentNode::ASTModuleAccessSharedValueAssignmentNode(std::shared_ptr<ASTModuleAccessExpressionNode> moduleAccessExpression, std::shared_ptr<ASTSharedValueAssignmentOperatorNode> assignmentOperator) {
    _moduleAccessExpression = moduleAccessExpression;
    _assignmentOperator = assignmentOperator;
    _children.push_back(_moduleAccessExpression);
    _children.push_back(_assignmentOperator);
}

std::shared_ptr<ASTModuleAccessExpressionNode> ASTModuleAccessSharedValueAssignmentNode::getModuleAccess() {
    return _moduleAccessExpression;
}

std::shared_ptr<TypeSignature> ASTModuleAccessSharedValueAssignmentNode::getTypeSignature() {
    return _moduleAccessExpression->getTypeSignature();
}

std::shared_ptr<Position> ASTModuleAccessSharedValueAssignmentNode::getStartPosition() {
    return _moduleAccessExpression->getStartPosition();
}

std::shared_ptr<Position> ASTModuleAccessSharedValueAssignmentNode::getEndPosition() {
    return _assignmentOperator->getEndPosition();
}

ASTNodeType ASTModuleAccessSharedValueAssignmentNode::getNodeType() {
    return AST_MODULE_ACCESS_SHARED_VALUE_ASSIGNMENT_NODE;
}

std::string ASTModuleAccessSharedValueAssignmentNode::toString() {
    return "MODULE_ACCESS_SHARED_VALUE_ASSIGNMENT";
}

bool ASTModuleAccessSharedValueAssignmentNode::isSameAs(std::shared_ptr<ASTNode> other) {
    if (!other->is(this->getNodeType())) {
        return false;
    }
    auto otherNode = std::dynamic_pointer_cast<ASTModuleAccessSharedValueAssignmentNode>(other);
    return this->getModuleAccess()->isSameAs(otherNode->getModuleAccess());
}

void ASTModuleAccessSharedValueAssignmentNode::print() {
    Logger::log("----------", this->toString(), "----------");
    _moduleAccessExpression->print();
    Logger::log("----------");
}

std::string ASTModuleAccessSharedValueAssignmentNode::toSourceCode() {
    auto sourceCodeBuilder = SourceCodeBuilder();
    sourceCodeBuilder.add(_moduleAccessExpression)
            ->add(_assignmentOperator);
    return sourceCodeBuilder.build();
}