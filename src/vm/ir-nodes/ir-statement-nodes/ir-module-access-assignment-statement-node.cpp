//
// Created by Johny Georges on 2026-04-02.
//

#include "ir-module-access-assignment-statement-node.h"

IRModuleAccessAssignmentStatementNode::IRModuleAccessAssignmentStatementNode(std::shared_ptr<ASTModuleAccessAssignmentStatementNode> node, IRModuleAccessExpressionNode* irModuleAccessExpression, IRExpressionNode* irExpression) {
    _node = node;
    _irModuleAccessExpression = irModuleAccessExpression;
    _irExpression = irExpression;
}

IRModuleAccessExpressionNode* IRModuleAccessAssignmentStatementNode::getIRModuleAccessExpression() {
    return _irModuleAccessExpression;
}

IRExpressionNode* IRModuleAccessAssignmentStatementNode::getIRExpression() {
    return _irExpression;
}

IRNodeType IRModuleAccessAssignmentStatementNode::getNodeType() {
    return IR_MODULE_ACCESS_ASSIGNMENT_STATEMENT_NODE;
}

std::string IRModuleAccessAssignmentStatementNode::toString() {
    return "IR_MODULE_ACCESS_ASSIGNMENT_STATEMENT_NODE";
}

void IRModuleAccessAssignmentStatementNode::print(std::unique_ptr<llvm::raw_fd_ostream> *stream) {
    _irModuleAccessExpression->print(stream);
    _irExpression->print(stream);
}