//
// Created by Johny Georges on 2026-06-27.
//

#include "ir-object-access-ref-assignment-statement-node.h"

IRObjectAccessRefAssignmentStatementNode::IRObjectAccessRefAssignmentStatementNode(std::shared_ptr<ASTObjectAccessRefAssignmentStatementNode> node, IRObjectAccessExpressionNode* irObjectAccessExpression, IRExpressionNode* irExpression) {
    _node = node;
    _irObjectAccessExpression = irObjectAccessExpression;
    _irExpression = irExpression;
}

IRObjectAccessExpressionNode* IRObjectAccessRefAssignmentStatementNode::getIRObjectAccessExpression() {
    return _irObjectAccessExpression;
}

IRExpressionNode* IRObjectAccessRefAssignmentStatementNode::getIRExpression() {
    return _irExpression;
}

IRNodeType IRObjectAccessRefAssignmentStatementNode::getNodeType() {
    return IR_OBJECT_ACCESS_REF_ASSIGNMENT_STATEMENT_NODE;
}

std::string IRObjectAccessRefAssignmentStatementNode::toString() {
    return "IR_OBJECT_ACCESS_REF_ASSIGNMENT_STATEMENT_NODE";
}

void IRObjectAccessRefAssignmentStatementNode::print(std::unique_ptr<llvm::raw_fd_ostream> *stream) {
    _irObjectAccessExpression->print(stream);
    _irExpression->print(stream);
}