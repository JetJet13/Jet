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

#include "ast-class-property-assignment-statement-node.h"
#include "../../../../shared/utils/logger/logger.h"
#include "../../types/source-code-builder/source-code-builder.h"

ASTClassPropertyAssignmentStatementNode::ASTClassPropertyAssignmentStatementNode(std::shared_ptr<ASTClassPropertyAssignmentNode> propertyAssignment, std::shared_ptr<ASTExpressionNode> expression) {
    _propertyAssignment = propertyAssignment;
    _expression = expression;
    _children.push_back(_propertyAssignment);
    _children.push_back(_expression);
}

std::shared_ptr<ASTClassPropertyAssignmentNode> ASTClassPropertyAssignmentStatementNode::getPropertyAssignment() {
    return _propertyAssignment;
}

std::shared_ptr<ASTExpressionNode> ASTClassPropertyAssignmentStatementNode::getExpression() {
    return _expression;
}

std::shared_ptr<Position> ASTClassPropertyAssignmentStatementNode::getStartPosition() {
    return _propertyAssignment->getStartPosition();
}

std::shared_ptr<Position> ASTClassPropertyAssignmentStatementNode::getEndPosition() {
    return _expression->getEndPosition();
}

ASTNodeType ASTClassPropertyAssignmentStatementNode::getNodeType() {
    return AST_CLASS_PROPERTY_ASSIGNMENT_STATEMENT_NODE;
}

std::string ASTClassPropertyAssignmentStatementNode::toString() {
    return "CLASS_PROPERTY_ASSIGNMENT_STATEMENT";
}

bool ASTClassPropertyAssignmentStatementNode::isSameAs(std::shared_ptr<ASTNode> other) {
    if (!other->is(this->getNodeType())) {
        return false;
    }
    auto otherNode = std::dynamic_pointer_cast<ASTClassPropertyAssignmentStatementNode>(other);
    return this->getPropertyAssignment()->isSameAs(otherNode->getPropertyAssignment()) &&
           this->getExpression()->isSameAs(otherNode->getExpression());
}

void ASTClassPropertyAssignmentStatementNode::print() {
    Logger::log("----------", this->toString(), "----------");
    _propertyAssignment->print();
    _expression->print();
    Logger::log("----------");
}

std::string ASTClassPropertyAssignmentStatementNode::toSourceCode() {
    auto sourceCodeBuilder = SourceCodeBuilder();
    sourceCodeBuilder.add(_propertyAssignment)
    ->add(_expression);
    return sourceCodeBuilder.build();
}