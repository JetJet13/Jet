//
// Created by Johny Georges on 2026-06-27.
//

#include "ir-module-access-ref-assignment-statement-node.h"

IRModuleAccessRefAssignmentStatementNode::IRModuleAccessRefAssignmentStatementNode(std::shared_ptr<ASTModuleAccessRefAssignmentStatementNode> node, IRModuleAccessExpressionNode* irModuleAccessExpression, IRExpressionNode* irExpression) {
    _node = node;
    _irModuleAccessExpression = irModuleAccessExpression;
    _irExpression = irExpression;
}

IRModuleAccessExpressionNode* IRModuleAccessRefAssignmentStatementNode::getIRModuleAccessExpression() {
    return _irModuleAccessExpression;
}

IRExpressionNode* IRModuleAccessRefAssignmentStatementNode::getIRExpression() {
    return _irExpression;
}

IRNodeType IRModuleAccessRefAssignmentStatementNode::getNodeType() {
    return IR_MODULE_ACCESS_REF_ASSIGNMENT_STATEMENT_NODE;
}

std::string IRModuleAccessRefAssignmentStatementNode::toString() {
    return "IR_MODULE_ACCESS_REF_ASSIGNMENT_STATEMENT_NODE";
}

void IRModuleAccessRefAssignmentStatementNode::print(std::unique_ptr<llvm::raw_fd_ostream> *stream) {
    _irModuleAccessExpression->print(stream);
    _irExpression->print(stream);
}