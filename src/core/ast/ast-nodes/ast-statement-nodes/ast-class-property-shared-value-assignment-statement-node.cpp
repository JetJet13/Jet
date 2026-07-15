//
// Created by Johny Georges on 2026-02-18.
//

#include "ast-class-property-shared-value-assignment-statement-node.h"
#include "../../../../shared/utils/logger/logger.h"
#include "../../types/source-code-builder/source-code-builder.h"

ASTClassPropertySharedValueAssignmentStatementNode::ASTClassPropertySharedValueAssignmentStatementNode(std::shared_ptr<ASTClassPropertySharedValueAssignmentNode> propertyAssignment, std::shared_ptr<ASTExpressionNode> expression) {
    _propertyAssignment = propertyAssignment;
    _expression = expression;
    _children.push_back(_propertyAssignment);
    _children.push_back(_expression);
}

std::shared_ptr<ASTClassPropertySharedValueAssignmentNode> ASTClassPropertySharedValueAssignmentStatementNode::getPropertyAssignment() {
    return _propertyAssignment;
}

std::shared_ptr<ASTExpressionNode> ASTClassPropertySharedValueAssignmentStatementNode::getExpression() {
    return _expression;
}

std::shared_ptr<Position> ASTClassPropertySharedValueAssignmentStatementNode::getStartPosition() {
    return _propertyAssignment->getStartPosition();
}

std::shared_ptr<Position> ASTClassPropertySharedValueAssignmentStatementNode::getEndPosition() {
    return _expression->getEndPosition();
}

ASTNodeType ASTClassPropertySharedValueAssignmentStatementNode::getNodeType() {
    return AST_CLASS_PROPERTY_SHARED_VALUE_ASSIGNMENT_STATEMENT_NODE;
}

std::string ASTClassPropertySharedValueAssignmentStatementNode::toString() {
    return "CLASS_PROPERTY_SHARED_VALUE_ASSIGNMENT_STATEMENT";
}

bool ASTClassPropertySharedValueAssignmentStatementNode::isSameAs(std::shared_ptr<ASTNode> other) {
    if (!other->is(this->getNodeType())) {
        return false;
    }
    auto otherNode = std::dynamic_pointer_cast<ASTClassPropertySharedValueAssignmentStatementNode>(other);
    return this->getPropertyAssignment()->isSameAs(otherNode->getPropertyAssignment()) &&
           this->getExpression()->isSameAs(otherNode->getExpression());
}

void ASTClassPropertySharedValueAssignmentStatementNode::print() {
    Logger::log("----------", this->toString(), "----------");
    _propertyAssignment->print();
    _expression->print();
    Logger::log("----------");
}

std::string ASTClassPropertySharedValueAssignmentStatementNode::toSourceCode() {
    auto sourceCodeBuilder = SourceCodeBuilder();
    sourceCodeBuilder.add(_propertyAssignment)
            ->add(_expression);
    return sourceCodeBuilder.build();
}