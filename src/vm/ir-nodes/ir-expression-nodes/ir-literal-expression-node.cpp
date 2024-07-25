//
// Created by Johny Georges on 2024-07-02.
//

#include "ir-literal-expression-node.h"

IRLiteralExpressionNode::IRLiteralExpressionNode(ASTLiteralExpressionNode* node, IRLiteralNode* irValue) {
    _node = node;
    _irValue = irValue;
}

llvm::Value* IRLiteralExpressionNode::insertSelfIntoBlock(std::unique_ptr<llvm::IRBuilder<>>*  builder) {
    return _irValue->getConstantIRValue();
}

IRType* IRLiteralExpressionNode::getIRType() {
    return _irValue->getIRType();
}

llvm::Constant* IRLiteralExpressionNode::getValue() {
    return _irValue->getConstantIRValue();
}

IRNodeType IRLiteralExpressionNode::getNodeType() {
    return IR_LITERAL_EXPRESSION_NODE;
}

std::string IRLiteralExpressionNode::toString() {
    return "IR_LITERAL_EXPRESSION_NODE";
}

void IRLiteralExpressionNode::print(std::unique_ptr<llvm::raw_fd_ostream> *stream) {
    _irValue->print(stream);
}