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

#include "ast-module-access-shared-value-assignment-statement-node.h"
#include "../../../../shared/utils/logger/logger.h"
#include "../../types/source-code-builder/source-code-builder.h"

ASTModuleAccessSharedValueAssignmentStatementNode::ASTModuleAccessSharedValueAssignmentStatementNode(std::shared_ptr<ASTModuleAccessSharedValueAssignmentNode> moduleAccessAssignment, std::shared_ptr<ASTExpressionNode> expression) {
    _moduleAccessAssignment = moduleAccessAssignment;
    _expression = expression;
    _children.push_back(_moduleAccessAssignment);
    _children.push_back(_expression);
}

std::shared_ptr<ASTModuleAccessSharedValueAssignmentNode> ASTModuleAccessSharedValueAssignmentStatementNode::getModuleAccessAssignment() {
    return _moduleAccessAssignment;
}

std::shared_ptr<ASTExpressionNode> ASTModuleAccessSharedValueAssignmentStatementNode::getExpression() {
    return _expression;
}

std::shared_ptr<Position> ASTModuleAccessSharedValueAssignmentStatementNode::getStartPosition() {
    return _moduleAccessAssignment->getStartPosition();
}

std::shared_ptr<Position> ASTModuleAccessSharedValueAssignmentStatementNode::getEndPosition() {
    return _expression->getEndPosition();
}

ASTNodeType ASTModuleAccessSharedValueAssignmentStatementNode::getNodeType() {
    return AST_MODULE_ACCESS_SHARED_VALUE_ASSIGNMENT_STATEMENT_NODE;
}

std::string ASTModuleAccessSharedValueAssignmentStatementNode::toString() {
    return "MODULE_ACCESS_SHARED_VALUE_ASSIGNMENT_STATEMENT";
}

bool ASTModuleAccessSharedValueAssignmentStatementNode::isSameAs(std::shared_ptr<ASTNode> other) {
    if (!other->is(this->getNodeType())) {
        return false;
    }
    auto otherNode = std::dynamic_pointer_cast<ASTModuleAccessSharedValueAssignmentStatementNode>(other);
    return this->getModuleAccessAssignment()->isSameAs(otherNode->getModuleAccessAssignment()) &&
           this->getExpression()->isSameAs(otherNode->getExpression());
}

void ASTModuleAccessSharedValueAssignmentStatementNode::print() {
    Logger::log("----------", this->toString(), "----------");
    _moduleAccessAssignment->print();
    _expression->print();
    Logger::log("----------");
}

std::string ASTModuleAccessSharedValueAssignmentStatementNode::toSourceCode() {
    auto sourceCodeBuilder = SourceCodeBuilder();
    sourceCodeBuilder.add(_moduleAccessAssignment)
            ->add(_expression);
    return sourceCodeBuilder.build();
}