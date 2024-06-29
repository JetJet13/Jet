//
// Created by Johny Georges on 2024-06-29.
//

#include "ir-binary-arithmetic-expression-node.h"

IRBinaryArithmeticExpressionNode::IRBinaryArithmeticExpressionNode(ASTBinaryExpressionNode* astBinaryExpressionNode, llvm::BinaryOperator* irValue) {
    _astNode = astBinaryExpressionNode;
    _irValue = irValue;
}

llvm::BinaryOperator* IRBinaryArithmeticExpressionNode::getIRValue() {
    return _irValue;
}

IRNodeType IRBinaryArithmeticExpressionNode::getNodeType() {
    return IR_BINARY_ARITHMETIC_EXPRESSION_NODE;
}

std::string IRBinaryArithmeticExpressionNode::toString() {
    return "IR_BINARY_ARITHMETIC_EXPRESSION_NODE";
}
