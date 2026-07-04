//
// Created by Johny Georges on 2026-02-18.
//

#include "ast-class-property-ref-value-assignment-statement-node.h"
#include "../../../../shared/utils/logger/logger.h"
#include "../../types/source-code-builder/source-code-builder.h"

ASTClassPropertyRefValueAssignmentStatementNode::ASTClassPropertyRefValueAssignmentStatementNode(std::shared_ptr<ASTClassPropertyRefValueAssignmentNode> propertyAssignment, std::shared_ptr<ASTExpressionNode> expression) {
    _propertyAssignment = propertyAssignment;
    _expression = expression;
    _children.push_back(_propertyAssignment);
    _children.push_back(_expression);
}

std::shared_ptr<ASTClassPropertyRefValueAssignmentNode> ASTClassPropertyRefValueAssignmentStatementNode::getPropertyAssignment() {
    return _propertyAssignment;
}

std::shared_ptr<ASTExpressionNode> ASTClassPropertyRefValueAssignmentStatementNode::getExpression() {
    return _expression;
}

Position* ASTClassPropertyRefValueAssignmentStatementNode::getStartPosition() {
    return _propertyAssignment->getStartPosition();
}

Position* ASTClassPropertyRefValueAssignmentStatementNode::getEndPosition() {
    return _expression->getEndPosition();
}

ASTNodeType ASTClassPropertyRefValueAssignmentStatementNode::getNodeType() {
    return AST_CLASS_PROPERTY_REF_VALUE_ASSIGNMENT_STATEMENT_NODE;
}

std::string ASTClassPropertyRefValueAssignmentStatementNode::toString() {
    return "CLASS_PROPERTY_REF_VALUE_ASSIGNMENT_STATEMENT";
}

bool ASTClassPropertyRefValueAssignmentStatementNode::isSameAs(std::shared_ptr<ASTNode> other) {
    if (!other->is(this->getNodeType())) {
        return false;
    }
    auto otherNode = std::dynamic_pointer_cast<ASTClassPropertyRefValueAssignmentStatementNode>(other);
    return this->getPropertyAssignment()->isSameAs(otherNode->getPropertyAssignment()) &&
           this->getExpression()->isSameAs(otherNode->getExpression());
}

void ASTClassPropertyRefValueAssignmentStatementNode::print() {
    Logger::log("----------", this->toString(), "----------");
    _propertyAssignment->print();
    _expression->print();
    Logger::log("----------");
}

std::string ASTClassPropertyRefValueAssignmentStatementNode::toSourceCode() {
    auto sourceCodeBuilder = SourceCodeBuilder();
    sourceCodeBuilder.add(_propertyAssignment)
            ->add(_expression);
    return sourceCodeBuilder.build();
}