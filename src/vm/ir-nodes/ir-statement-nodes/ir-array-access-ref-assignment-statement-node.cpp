//
// Created by Johny Georges on 2026-06-27.
//

#include "ir-array-access-ref-assignment-statement-node.h"

IRArrayAccessRefAssignmentStatementNode::IRArrayAccessRefAssignmentStatementNode(std::shared_ptr<ASTArrayAccessRefAssignmentStatementNode> node, std::shared_ptr<IRArrayAccessExpressionNode> irArrayAccessExpression, std::shared_ptr<IRExpressionNode> irExpression) {
    _node = node;
    _irArrayAccessExpression = irArrayAccessExpression;
    _irExpression = irExpression;
}

std::shared_ptr<IRArrayAccessExpressionNode> IRArrayAccessRefAssignmentStatementNode::getIRArrayAccessExpression() {
    return _irArrayAccessExpression;
}

std::shared_ptr<IRExpressionNode> IRArrayAccessRefAssignmentStatementNode::getIRExpression() {
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