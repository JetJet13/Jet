//
// Created by Johny Georges on 2026-02-20.
//

#include "ir-shared-value-assignment-statement-node.h"

IRSharedValueAssignmentStatementNode::IRSharedValueAssignmentStatementNode(std::shared_ptr<ASTSharedValueAssignmentStatementNode> node, std::shared_ptr<IRExpressionNode> irExpression) {
    _node = node;
    _irExpression = irExpression;
}

std::string IRSharedValueAssignmentStatementNode::getVariableName() {
    return _node->getVariableAssignment()->getIdentifierNode()->getId();
}

std::shared_ptr<IRExpressionNode> IRSharedValueAssignmentStatementNode::getIRExpression() {
    return _irExpression;
}

IRNodeType IRSharedValueAssignmentStatementNode::getNodeType() {
    return IR_SHARED_VALUE_ASSIGNMENT_STATEMENT_NODE;
}

std::string IRSharedValueAssignmentStatementNode::toString() {
    return "IR_SHARED_VALUE_ASSIGNMENT_STATEMENT_NODE";
}

void IRSharedValueAssignmentStatementNode::print(std::unique_ptr<llvm::raw_fd_ostream> *stream) {
    _irExpression->print(stream);
}