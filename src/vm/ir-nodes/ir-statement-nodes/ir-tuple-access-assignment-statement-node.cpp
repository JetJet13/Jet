//
// Created by Johny Georges on 2025-10-16.
//

#include "ir-tuple-access-assignment-statement-node.h"

IRTupleAccessAssignmentStatementNode::IRTupleAccessAssignmentStatementNode(std::shared_ptr<ASTTupleAccessAssignmentStatementNode> node, IRTupleAccessExpressionNode* irTupleAccessExpression, IRExpressionNode* irExpression) {
    _node = node;
    _irTupleAccessExpression = irTupleAccessExpression;
    _irExpression = irExpression;
}

IRTupleAccessExpressionNode* IRTupleAccessAssignmentStatementNode::getIRTupleAccessExpression() {
    return _irTupleAccessExpression;
}

IRExpressionNode* IRTupleAccessAssignmentStatementNode::getIRExpression() {
    return _irExpression;
}

IRNodeType IRTupleAccessAssignmentStatementNode::getNodeType() {
    return IR_TUPLE_ACCESS_ASSIGNMENT_STATEMENT_NODE;
}

std::string IRTupleAccessAssignmentStatementNode::toString() {
    return "IR_TUPLE_ACCESS_ASSIGNMENT_STATEMENT_NODE";
}

void IRTupleAccessAssignmentStatementNode::print(std::unique_ptr<llvm::raw_fd_ostream> *stream) {
    _irTupleAccessExpression->print(stream);
    _irExpression->print(stream);
}