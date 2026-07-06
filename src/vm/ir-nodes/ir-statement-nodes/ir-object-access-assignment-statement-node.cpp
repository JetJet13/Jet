//
// Created by Johny Georges on 2025-08-30.
//

#include "ir-object-access-assignment-statement-node.h"

IRObjectAccessAssignmentStatementNode::IRObjectAccessAssignmentStatementNode(std::shared_ptr<ASTObjectAccessAssignmentStatementNode> node, std::shared_ptr<IRObjectAccessExpressionNode> irObjectAccessExpression, std::shared_ptr<IRExpressionNode> irExpression) {
    _node = node;
    _irObjectAccessExpression = irObjectAccessExpression;
    _irExpression = irExpression;
}

std::shared_ptr<IRObjectAccessExpressionNode> IRObjectAccessAssignmentStatementNode::getIRObjectAccessExpression() {
    return _irObjectAccessExpression;
}

std::shared_ptr<IRExpressionNode> IRObjectAccessAssignmentStatementNode::getIRExpression() {
    return _irExpression;
}

IRNodeType IRObjectAccessAssignmentStatementNode::getNodeType() {
    return IR_OBJECT_ACCESS_ASSIGNMENT_STATEMENT_NODE;
}

std::string IRObjectAccessAssignmentStatementNode::toString() {
    return "IR_OBJECT_ACCESS_ASSIGNMENT_STATEMENT_NODE";
}

void IRObjectAccessAssignmentStatementNode::print(std::unique_ptr<llvm::raw_fd_ostream> *stream) {
    _irObjectAccessExpression->print(stream);
    _irExpression->print(stream);
}