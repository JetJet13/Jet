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
// Created by Johny Georges on 2024-03-22.
//

#include "ast-variable-assignment-statement-node.h"
#include "../../../../shared/utils/logger/logger.h"
#include "../../types/source-code-builder/source-code-builder.h"

ASTVariableAssignmentStatementNode::ASTVariableAssignmentStatementNode(std::shared_ptr<ASTVariableAssignmentNode> variable, std::shared_ptr<ASTExpressionNode> expression) {
    _variableAssignment = variable;
    _expression = expression;
    _children.push_back(_variableAssignment);
    _children.push_back(_expression);
}

std::shared_ptr<ASTVariableAssignmentNode> ASTVariableAssignmentStatementNode::getVariableAssignment() {
    return _variableAssignment;
}

std::shared_ptr<ASTExpressionNode> ASTVariableAssignmentStatementNode::getExpression() {
    return _expression;
}

std::shared_ptr<Position> ASTVariableAssignmentStatementNode::getStartPosition() {
    return _variableAssignment->getStartPosition();
}

std::shared_ptr<Position> ASTVariableAssignmentStatementNode::getEndPosition() {
    return _expression->getEndPosition();
}

ASTNodeType ASTVariableAssignmentStatementNode::getNodeType() {
    return AST_VARIABLE_ASSIGNMENT_STATEMENT_NODE;
}

std::string ASTVariableAssignmentStatementNode::toString() {
    return "VARIABLE_ASSIGNMENT_STATEMENT";
}

bool ASTVariableAssignmentStatementNode::isSameAs(std::shared_ptr<ASTNode> other) {
    if (!other->is(this->getNodeType())) {
        return false;
    }
    auto otherNode = std::dynamic_pointer_cast<ASTVariableAssignmentStatementNode>(other);
    return this->getVariableAssignment()->isSameAs(otherNode->getVariableAssignment()) &&
           this->getExpression()->isSameAs(otherNode->getExpression());
}

void ASTVariableAssignmentStatementNode::print() {
    Logger::log("----------", this->toString(), "----------");
    _variableAssignment->print();
    _expression->print();
    Logger::log("----------");
}

std::string ASTVariableAssignmentStatementNode::toSourceCode() {
    auto sourceCodeBuilder = SourceCodeBuilder();
    sourceCodeBuilder.add(_variableAssignment)
    ->add(_expression);
    return sourceCodeBuilder.build();
}