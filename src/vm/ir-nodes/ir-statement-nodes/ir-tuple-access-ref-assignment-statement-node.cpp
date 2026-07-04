//
// Created by Johny Georges on 2026-06-27.
//

#include "ir-tuple-access-ref-assignment-statement-node.h"

IRTupleAccessRefAssignmentStatementNode::IRTupleAccessRefAssignmentStatementNode(std::shared_ptr<ASTTupleAccessRefAssignmentStatementNode> node, IRTupleAccessExpressionNode* irTupleAccessExpression, IRExpressionNode* irExpression) {
    _node = node;
    _irTupleAccessExpression = irTupleAccessExpression;
    _irExpression = irExpression;
}

IRTupleAccessExpressionNode* IRTupleAccessRefAssignmentStatementNode::getIRTupleAccessExpression() {
    return _irTupleAccessExpression;
}

IRExpressionNode* IRTupleAccessRefAssignmentStatementNode::getIRExpression() {
    return _irExpression;
}

IRNodeType IRTupleAccessRefAssignmentStatementNode::getNodeType() {
    return IR_TUPLE_ACCESS_REF_ASSIGNMENT_STATEMENT_NODE;
}

std::string IRTupleAccessRefAssignmentStatementNode::toString() {
    return "IR_TUPLE_ACCESS_REF_ASSIGNMENT_STATEMENT_NODE";
}

void IRTupleAccessRefAssignmentStatementNode::print(std::unique_ptr<llvm::raw_fd_ostream> *stream) {
    _irTupleAccessExpression->print(stream);
    _irExpression->print(stream);
}