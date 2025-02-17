//
// Created by Johny Georges on 2025-02-17.
//

#include "ir-array-access-assignment-statement-node.h"

IRArrayAccessAssignmentStatementNode::IRArrayAccessAssignmentStatementNode(ASTArrayAccessAssignmentStatementNode* node, IRArrayAccessExpressionNode* irArrayAccessExpression, IRExpressionNode* irExpression) {
    _node = node;
    _irArrayAccessExpression = irArrayAccessExpression;
    _irExpression = irExpression;
}

IRArrayAccessExpressionNode* IRArrayAccessAssignmentStatementNode::getIRArrayAccessExpression() {
    return _irArrayAccessExpression;
}

IRExpressionNode* IRArrayAccessAssignmentStatementNode::getIRExpression() {
    return _irExpression;
}

IRNodeType IRArrayAccessAssignmentStatementNode::getNodeType() {
    return IR_ARRAY_ACCESS_ASSIGNMENT_STATEMENT_NODE;
}

std::string IRArrayAccessAssignmentStatementNode::toString() {
    return "IR_ARRAY_ACCESS_ASSIGNMENT_STATEMENT_NODE";
}

void IRArrayAccessAssignmentStatementNode::print(std::unique_ptr<llvm::raw_fd_ostream> *stream) {
    _irArrayAccessExpression->print(stream);
    _irExpression->print(stream);
}