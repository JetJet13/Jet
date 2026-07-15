//
// Created by Johny Georges on 2026-06-27.
//

#include "ir-tuple-access-shared-value-assignment-statement-node.h"

IRTupleAccessSharedValueAssignmentStatementNode::IRTupleAccessSharedValueAssignmentStatementNode(std::shared_ptr<ASTTupleAccessSharedValueAssignmentStatementNode> node, std::shared_ptr<IRTupleAccessExpressionNode> irTupleAccessExpression, std::shared_ptr<IRExpressionNode> irExpression) {
    _node = node;
    _irTupleAccessExpression = irTupleAccessExpression;
    _irExpression = irExpression;
}

std::shared_ptr<IRTupleAccessExpressionNode> IRTupleAccessSharedValueAssignmentStatementNode::getIRTupleAccessExpression() {
    return _irTupleAccessExpression;
}

std::shared_ptr<IRExpressionNode> IRTupleAccessSharedValueAssignmentStatementNode::getIRExpression() {
    return _irExpression;
}

IRNodeType IRTupleAccessSharedValueAssignmentStatementNode::getNodeType() {
    return IR_TUPLE_ACCESS_SHARED_VALUE_ASSIGNMENT_STATEMENT_NODE;
}

std::string IRTupleAccessSharedValueAssignmentStatementNode::toString() {
    return "IR_TUPLE_ACCESS_SHARED_VALUE_ASSIGNMENT_STATEMENT_NODE";
}

void IRTupleAccessSharedValueAssignmentStatementNode::print(std::unique_ptr<llvm::raw_fd_ostream> *stream) {
    _irTupleAccessExpression->print(stream);
    _irExpression->print(stream);
}