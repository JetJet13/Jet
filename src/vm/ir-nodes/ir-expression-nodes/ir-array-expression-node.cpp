//
// Created by Johny Georges on 2024-07-01.
//

#include "ir-array-expression-node.h"

IRArrayExpressionNode::IRArrayExpressionNode(ASTArrayExpressionNode* astNode, llvm::Constant* irValue) {
    _astNode = astNode;
    _irValue = irValue;
}

llvm::Value * IRArrayExpressionNode::insertSelfIntoBlock(std::unique_ptr<llvm::IRBuilder<>>*  builder, llvm::Value *parent) {
    return builder->get()->CreateStore(_irValue, parent);
}

llvm::Constant* IRArrayExpressionNode::getConstantIRValue() {
    return _irValue;
}

llvm::Constant* IRArrayExpressionNode::getIRValue() {
    return _irValue;
}

llvm::Type* IRArrayExpressionNode::getIRTypeAtIndex(unsigned long index) {
    return _irValue->getType()->getArrayElementType();
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