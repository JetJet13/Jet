//
// Created by Johny Georges on 2024-04-20.
//

#include "ast-class-property-assignment-statement-node.h"
#include "../../../../shared/utils/logger/logger.h"

ASTClassPropertyAssignmentStatementNode::ASTClassPropertyAssignmentStatementNode(ASTClassPropertyAssignmentNode* propertyAssignment, ASTExpressionNode* expression) {
    _propertyAssignment = propertyAssignment;
    _expression = expression;
    _children.push_back(_propertyAssignment);
    _children.push_back(_expression);
}

ASTClassPropertyAssignmentNode* ASTClassPropertyAssignmentStatementNode::getPropertyAssignment() {
    return _propertyAssignment;
}

ASTExpressionNode* ASTClassPropertyAssignmentStatementNode::getExpression() {
    return _expression;
}

ASTNodeType ASTClassPropertyAssignmentStatementNode::getNodeType() {
    return AST_CLASS_PROPERTY_ASSIGNMENT_STATEMENT_NODE;
}

std::string ASTClassPropertyAssignmentStatementNode::toString() {
    return "CLASS_PROPERTY_ASSIGNMENT_STATEMENT";
}

bool ASTClassPropertyAssignmentStatementNode::isSameAs(ASTNode* other) {
    if (!other->is(this->getNodeType())) {
        return false;
    }
    auto otherNode = (ASTClassPropertyAssignmentStatementNode*)other;
    return this->getPropertyAssignment()->isSameAs(otherNode->getPropertyAssignment()) &&
           this->getExpression()->isSameAs(otherNode->getExpression());
}

void ASTClassPropertyAssignmentStatementNode::print() {
    Logger::log("----------", this->toString(), "----------");
    _propertyAssignment->print();
    _expression->print();
    Logger::log("----------");
}