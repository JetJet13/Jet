//
// Created by Johny Georges on 2024-07-01.
//

#include "ir-unary-arithmetic-expression-node.h"

IRUnaryArithmeticExpressionNode::IRUnaryArithmeticExpressionNode(ASTUnaryExpressionNode* astNode, llvm::BinaryOperator* irValue) {
    _astNode = astNode;
    _irValue = irValue;
}

llvm::BinaryOperator* IRUnaryArithmeticExpressionNode::getIRValue() {
    return _irValue;
}

IRNodeType IRUnaryArithmeticExpressionNode::getNodeType() {
    return IR_UNARY_ARITHMETIC_EXPRESSION_NODE;
}

std::string IRUnaryArithmeticExpressionNode::toString() {
    return "IR_UNARY_EXPRESSION_NODE";
}