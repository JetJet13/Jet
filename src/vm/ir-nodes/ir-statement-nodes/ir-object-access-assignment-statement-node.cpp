//
// Created by Johny Georges on 2025-08-30.
//

#include "ir-object-access-assignment-statement-node.h"

IRObjectAccessAssignmentStatementNode::IRObjectAccessAssignmentStatementNode(std::shared_ptr<ASTObjectAccessAssignmentStatementNode> node, IRObjectAccessExpressionNode* irObjectAccessExpression, IRExpressionNode* irExpression) {
    _node = node;
    _irObjectAccessExpression = irObjectAccessExpression;
    _irExpression = irExpression;
}

IRObjectAccessExpressionNode* IRObjectAccessAssignmentStatementNode::getIRObjectAccessExpression() {
    return _irObjectAccessExpression;
}

IRExpressionNode* IRObjectAccessAssignmentStatementNode::getIRExpression() {
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