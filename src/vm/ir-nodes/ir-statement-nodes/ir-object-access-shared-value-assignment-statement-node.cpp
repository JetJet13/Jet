//
// Created by Johny Georges on 2026-06-27.
//

#include "ir-object-access-shared-value-assignment-statement-node.h"

IRObjectAccessSharedValueAssignmentStatementNode::IRObjectAccessSharedValueAssignmentStatementNode(std::shared_ptr<ASTObjectAccessSharedValueAssignmentStatementNode> node, std::shared_ptr<IRObjectAccessExpressionNode> irObjectAccessExpression, std::shared_ptr<IRExpressionNode> irExpression) {
    _node = node;
    _irObjectAccessExpression = irObjectAccessExpression;
    _irExpression = irExpression;
}

std::shared_ptr<IRObjectAccessExpressionNode> IRObjectAccessSharedValueAssignmentStatementNode::getIRObjectAccessExpression() {
    return _irObjectAccessExpression;
}

std::shared_ptr<IRExpressionNode> IRObjectAccessSharedValueAssignmentStatementNode::getIRExpression() {
    return _irExpression;
}

IRNodeType IRObjectAccessSharedValueAssignmentStatementNode::getNodeType() {
    return IR_OBJECT_ACCESS_SHARED_VALUE_ASSIGNMENT_STATEMENT_NODE;
}

std::string IRObjectAccessSharedValueAssignmentStatementNode::toString() {
    return "IR_OBJECT_ACCESS_SHARED_VALUE_ASSIGNMENT_STATEMENT_NODE";
}

void IRObjectAccessSharedValueAssignmentStatementNode::print(std::unique_ptr<llvm::raw_fd_ostream> *stream) {
    _irObjectAccessExpression->print(stream);
    _irExpression->print(stream);
}