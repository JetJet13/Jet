//
// Created by Johny Georges on 2024-07-01.
//

#include "ir-array-expression-node.h"

IRArrayExpressionNode::IRArrayExpressionNode(ASTArrayExpressionNode* astNode, llvm::Constant* irValue) {
    _astNode = astNode;
    _irValue = irValue;
}

llvm::Constant* IRArrayExpressionNode::getConstantIRValue() {
    return _irValue;
}

llvm::Constant* IRArrayExpressionNode::getIRValue() {
    return _irValue;
}

IRNodeType IRArrayExpressionNode::getNodeType() {
    return IR_ARRAY_EXPRESSION_NODE;
}

std::string IRArrayExpressionNode::toString() {
    return "IR_ARRAY_EXPRESSION_NODE";
}

void IRArrayExpressionNode::print(std::unique_ptr<llvm::raw_fd_ostream> *stream) {
    _irValue->print(**stream);
}