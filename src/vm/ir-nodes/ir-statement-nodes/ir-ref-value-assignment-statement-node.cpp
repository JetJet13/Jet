//
// Created by Johny Georges on 2026-02-20.
//

#include "ir-ref-value-assignment-statement-node.h"

IRRefValueAssignmentStatementNode::IRRefValueAssignmentStatementNode(std::shared_ptr<ASTRefValueAssignmentStatementNode> node, IRExpressionNode* irExpression) {
    _node = node;
    _irExpression = irExpression;
}

std::string IRRefValueAssignmentStatementNode::getVariableName() {
    return _node->getVariableAssignment()->getIdentifierNode()->getId();
}

IRExpressionNode* IRRefValueAssignmentStatementNode::getIRExpression() {
    return _irExpression;
}

IRNodeType IRRefValueAssignmentStatementNode::getNodeType() {
    return IR_REF_VALUE_ASSIGNMENT_STATEMENT_NODE;
}

std::string IRRefValueAssignmentStatementNode::toString() {
    return "IR_REF_VALUE_ASSIGNMENT_STATEMENT_NODE";
}

void IRRefValueAssignmentStatementNode::print(std::unique_ptr<llvm::raw_fd_ostream> *stream) {
    _irExpression->print(stream);
}