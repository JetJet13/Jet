//
// Created by Johny Georges on 2024-07-01.
//

#include "ir-tuple-expression-node.h"

IRTupleExpressionNode::IRTupleExpressionNode(ASTTupleExpressionNode* astNode, llvm::Constant* irValue) {
    _astNode = astNode;
    _irValue = irValue;
}

llvm::Constant* IRTupleExpressionNode::getConstantIRValue() {
    return _irValue;
}

llvm::Constant* IRTupleExpressionNode::getIRValue() {
    return _irValue;
}

IRNodeType IRTupleExpressionNode::getNodeType() {
    return IR_TUPLE_EXPRESSION_NODE;
}

std::string IRTupleExpressionNode::toString() {
    return "IR_TUPLE_EXPRESSION_NODE";
}