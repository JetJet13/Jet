//
// Created by Johny Georges on 2026-06-27.
//

#include "ir-module-access-shared-value-assignment-statement-node.h"

IRModuleAccessSharedValueAssignmentStatementNode::IRModuleAccessSharedValueAssignmentStatementNode(std::shared_ptr<ASTModuleAccessSharedValueAssignmentStatementNode> node, std::shared_ptr<IRModuleAccessExpressionNode> irModuleAccessExpression, std::shared_ptr<IRExpressionNode> irExpression) {
    _node = node;
    _irModuleAccessExpression = irModuleAccessExpression;
    _irExpression = irExpression;
}

std::shared_ptr<IRModuleAccessExpressionNode> IRModuleAccessSharedValueAssignmentStatementNode::getIRModuleAccessExpression() {
    return _irModuleAccessExpression;
}

std::shared_ptr<IRExpressionNode> IRModuleAccessSharedValueAssignmentStatementNode::getIRExpression() {
    return _irExpression;
}

IRNodeType IRModuleAccessSharedValueAssignmentStatementNode::getNodeType() {
    return IR_MODULE_ACCESS_SHARED_VALUE_ASSIGNMENT_STATEMENT_NODE;
}

std::string IRModuleAccessSharedValueAssignmentStatementNode::toString() {
    return "IR_MODULE_ACCESS_SHARED_VALUE_ASSIGNMENT_STATEMENT_NODE";
}

void IRModuleAccessSharedValueAssignmentStatementNode::print(std::unique_ptr<llvm::raw_fd_ostream> *stream) {
    _irModuleAccessExpression->print(stream);
    _irExpression->print(stream);
}