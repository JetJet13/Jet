//
// Created by Johny Georges on 2026-06-27.
//

#include "ir-array-access-ref-assignment-statement-node.h"

IRArrayAccessRefAssignmentStatementNode::IRArrayAccessRefAssignmentStatementNode(ASTArrayAccessRefAssignmentStatementNode* node, IRArrayAccessExpressionNode* irArrayAccessExpression, IRExpressionNode* irExpression) {
    _node = node;
    _irArrayAccessExpression = irArrayAccessExpression;
    _irExpression = irExpression;
}

IRArrayAccessExpressionNode* IRArrayAccessRefAssignmentStatementNode::getIRArrayAccessExpression() {
    return _irArrayAccessExpression;
}

IRExpressionNode* IRArrayAccessRefAssignmentStatementNode::getIRExpression() {
    return _irExpression;
}

IRNodeType IRArrayAccessRefAssignmentStatementNode::getNodeType() {
    return IR_ARRAY_ACCESS_REF_ASSIGNMENT_STATEMENT_NODE;
}

std::string IRArrayAccessRefAssignmentStatementNode::toString() {
    return "IR_ARRAY_ACCESS_REF_ASSIGNMENT_STATEMENT_NODE";
}

void IRArrayAccessRefAssignmentStatementNode::print(std::unique_ptr<llvm::raw_fd_ostream> *stream) {
    _irArrayAccessExpression->print(stream);
    _irExpression->print(stream);
}