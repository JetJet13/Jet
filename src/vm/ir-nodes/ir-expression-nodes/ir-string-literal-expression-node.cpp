//
// Created by Johny Georges on 2024-08-05.
//

#include "ir-string-literal-expression-node.h"

IRStringLiteralExpressionNode::IRStringLiteralExpressionNode(ASTLiteralExpressionNode* node, IRStringLiteralNode* irValue, IRPointerType* irType, IRInstructionNode* sourceAllocation) {
    _node = node;
    _irValue = irValue;
    _irType = irType;
    _sourceAllocation = sourceAllocation;
}

llvm::Value* IRStringLiteralExpressionNode::insertSelfIntoBlock(std::unique_ptr<llvm::IRBuilder<>>*  builder) {
    auto arrayAllocation = builder->get()->CreateAlloca(_irValue->getConstantIRValue()->getType());
    builder->get()->CreateStore(_irValue->getConstantIRValue(), arrayAllocation);
    return _irValue->getIRArray()->insertSelfIntoBlock(builder, new IRInstructionNode(arrayAllocation, _irType));
}

IRPointerType* IRStringLiteralExpressionNode::getIRType() {
    return _irType;
}

llvm::Constant* IRStringLiteralExpressionNode::getValue() {
    return _irValue->getConstantIRValue();
}

IRInstructionNode* IRStringLiteralExpressionNode::getSourceAllocation() {
    return _sourceAllocation;
}

IRNodeType IRStringLiteralExpressionNode::getNodeType() {
    return IR_STRING_LITERAL_EXPRESSION_NODE;
}

std::string IRStringLiteralExpressionNode::toString() {
    return "IR_STRING_LITERAL_EXPRESSION_NODE";
}

void IRStringLiteralExpressionNode::print(std::unique_ptr<llvm::raw_fd_ostream> *stream) {
    _irValue->print(stream);
}