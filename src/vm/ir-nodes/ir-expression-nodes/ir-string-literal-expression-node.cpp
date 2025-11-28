//
// Created by Johny Georges on 2024-08-05.
//

#include "ir-string-literal-expression-node.h"

IRStringLiteralExpressionNode::IRStringLiteralExpressionNode(ASTLiteralExpressionNode* node, IRStringLiteralNode* irValue, IRArrayPointerType* irArrayPointerType, IRInstructionNode* sourceAllocation, IRInstructionNode* arrayPointerSourceAllocation) {
    _node = node;
    _irValue = irValue;
    _irArrayPointerType = irArrayPointerType;
    _sourceAllocation = sourceAllocation;
    _arrayPointerSourceAllocation = arrayPointerSourceAllocation;
}

bool IRStringLiteralExpressionNode::isReferenced() {
    return _node->isReferenced();
}

IRArrayPointerType* IRStringLiteralExpressionNode::getIRType() {
    return _irArrayPointerType;
}

TypeSignature* IRStringLiteralExpressionNode::getTypeSignature() {
    return _node->getTypeSignature();
}

llvm::Constant* IRStringLiteralExpressionNode::getValue() {
    return _irValue->getConstantIRValue();
}

std::optional<IRInstructionNode*> IRStringLiteralExpressionNode::getSourceAllocation() {
    return _arrayPointerSourceAllocation;
}

IRInstructionNode* IRStringLiteralExpressionNode::getSourceAggregateAllocation() {
    return _sourceAllocation;
}

IRInstructionNode* IRStringLiteralExpressionNode::getAggregatePointerAllocation() {
    return _arrayPointerSourceAllocation;
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