//
// Created by Johny Georges on 2024-03-22.
//

#include "ast-variable-assignment-statement-node.h"
#include "../../../../shared/utils/logger/logger.h"

ASTVariableAssignmentStatementNode::ASTVariableAssignmentStatementNode(ASTVariableAssignmentNode* variable, ASTExpressionNode* expression) {
    _variable = variable;
    _expression = expression;
}

ASTVariableAssignmentNode* ASTVariableAssignmentStatementNode::getVariable() {
    return _variable;
}

ASTExpressionNode* ASTVariableAssignmentStatementNode::getExpression() {
    return _expression;
}

ASTNodeType ASTVariableAssignmentStatementNode::getNodeType() {
    return AST_VARIABLE_ASSIGNMENT_STATEMENT_NODE;
}

std::string ASTVariableAssignmentStatementNode::toString() {
    return "VARIABLE_ASSIGNMENT_STATEMENT";
}

bool ASTVariableAssignmentStatementNode::isSameAs(ASTNode* other) {
    if (!other->is(this->getNodeType())) {
        return false;
    }
    auto otherNode = (ASTVariableAssignmentStatementNode*)other;
    return this->getVariable()->isSameAs(otherNode->getVariable()) &&
           this->getExpression()->isSameAs(otherNode->getExpression());
}

void ASTVariableAssignmentStatementNode::print() {
    Logger::log("----------", this->toString(), "----------");
    _variable->print();
    _expression->print();
    Logger::log("----------");
}