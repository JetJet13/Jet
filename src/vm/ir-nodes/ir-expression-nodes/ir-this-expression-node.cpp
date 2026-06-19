//
// Created by Johny Georges on 2026-06-15.
//

#include "ir-this-expression-node.h"
#include "../../../shared/utils/logger/logger.h"

IRThisExpressionNode::IRThisExpressionNode(ASTThisExpressionNode* node, IRInstructionNode* irValue) {
    _node = node;
    _irValue = irValue;
    _irType = (IRPointerType*)irValue->getIRType()->getSourceType()->clone();
}

llvm::Value* IRThisExpressionNode::getValue() {
    return _irValue->getValue();
}

IRInstructionNode* IRThisExpressionNode::getIRValue() {
    return _irValue;
}

std::optional<IRInstructionNode*> IRThisExpressionNode::getSourceAllocation() {
    return _irValue;
}

IRPointerType* IRThisExpressionNode::getIRType() {
    return _irType;
}

TypeSignature* IRThisExpressionNode::getTypeSignature() {
    return _node->getTypeSignature();
}

Position* IRThisExpressionNode::getStartPosition() {
    return _node->getStartPosition();
}

Position* IRThisExpressionNode::getEndPosition() {
    return _node->getEndPosition();
}

IRNodeType IRThisExpressionNode::getNodeType() {
    return IR_THIS_EXPRESSION_NODE;
}

std::string IRThisExpressionNode::toString() {
    return "IR_THIS_EXPRESSION_NODE";
}

void IRThisExpressionNode::print(std::unique_ptr<llvm::raw_fd_ostream> *stream) {
    _irValue->print(stream);
}