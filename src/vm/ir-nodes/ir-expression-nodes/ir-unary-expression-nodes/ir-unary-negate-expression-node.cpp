//
// Created by Johny Georges on 2024-07-01.
//

#include "ir-unary-negate-expression-node.h"

IRUnaryNegateExpressionNode::IRUnaryNegateExpressionNode(ASTUnaryExpressionNode* astNode, llvm::UnaryOperator* irValue) {
    _astNode = astNode;
    _irValue = irValue;
}

llvm::UnaryOperator* IRUnaryNegateExpressionNode::getIRValue() {
    return _irValue;
}

IRNodeType IRUnaryNegateExpressionNode::getNodeType() {
    return IR_UNARY_EXPRESSION_NODE;
}

std::string IRUnaryNegateExpressionNode::toString() {
    return "IR_UNARY_EXPRESSION_NODE";
}