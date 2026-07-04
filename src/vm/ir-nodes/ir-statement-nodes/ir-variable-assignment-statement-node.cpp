//
// Created by Johny Georges on 2025-01-06.
//

#include "ir-variable-assignment-statement-node.h"

IRVariableAssignmentStatementNode::IRVariableAssignmentStatementNode(std::shared_ptr<ASTVariableAssignmentStatementNode> node, IRExpressionNode* irExpression) {
    _node = node;
    _irExpression = irExpression;
}

std::string IRVariableAssignmentStatementNode::getVariableName() {
    return _node->getVariableAssignment()->getIdentifierNode()->getId();
}

IRExpressionNode* IRVariableAssignmentStatementNode::getIRExpression() {
    return _irExpression;
}

IRNodeType IRVariableAssignmentStatementNode::getNodeType() {
    return IR_VARIABLE_ASSIGNMENT_STATEMENT_NODE;
}

std::string IRVariableAssignmentStatementNode::toString() {
    return "IR_VARIABLE_ASSIGNMENT_STATEMENT_NODE";
}

void IRVariableAssignmentStatementNode::print(std::unique_ptr<llvm::raw_fd_ostream> *stream) {
    _irExpression->print(stream);
}