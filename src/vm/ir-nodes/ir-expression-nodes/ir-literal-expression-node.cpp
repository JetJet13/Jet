//
// Created by Johny Georges on 2024-07-02.
//

#include "ir-literal-expression-node.h"

IRLiteralExpressionNode::IRLiteralExpressionNode(ASTLiteralExpressionNode* node, IRLiteralNode* irValue, IRPointerType* irType, IRInstructionNode* sourceAllocation) {
    _node = node;
    _irValue = irValue;
    _irType = irType;
    _sourceAllocation = sourceAllocation;
}

llvm::Value* IRLiteralExpressionNode::insertSelfIntoBlock(std::unique_ptr<llvm::IRBuilder<>>*  builder) {
    auto allocation = builder->get()->Insert(_sourceAllocation->getValue());
    builder->get()->CreateStore(_irValue->getConstantIRValue(), allocation);
    return allocation;
}

IRPointerType* IRLiteralExpressionNode::getIRType() {
    return _irType;
}

llvm::Constant* IRLiteralExpressionNode::getValue() {
    return _irValue->getConstantIRValue();
}

IRInstructionNode* IRLiteralExpressionNode::getSourceAllocation() {
    return _sourceAllocation;
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