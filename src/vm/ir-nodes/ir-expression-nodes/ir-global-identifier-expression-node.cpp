//
// Created by Johny Georges on 2024-07-17.
//

#include "ir-global-identifier-expression-node.h"

IRGlobalIdentifierExpressionNode::IRGlobalIdentifierExpressionNode(ASTIdentifierExpressionNode* node, IRInstructionNode* irValue) {
    _node = node;
    _irValue = irValue;
}

std::optional<IRInstructionNode*> IRGlobalIdentifierExpressionNode::getSourceAllocation() {
    return _irValue->getParentAllocation();
}

llvm::GlobalVariable* IRGlobalIdentifierExpressionNode::getValue() {
    return (llvm::GlobalVariable*)_irValue->getValue();
}

IRPointerType* IRGlobalIdentifierExpressionNode::getIRType() {
    return _irValue->getIRType();
}

TypeSignature* IRGlobalIdentifierExpressionNode::getTypeSignature() {
    return _node->getTypeSignature();
}

llvm::Type* IRGlobalIdentifierExpressionNode::getType() {
    return _irValue->getAllocatedType();
}

llvm::Type* IRGlobalIdentifierExpressionNode::getTypeAtIndex(unsigned long index) {
    return _irValue->getIRType()->getSourceType()->getType();
}

IRNodeType IRGlobalIdentifierExpressionNode::getNodeType() {
    return IR_GLOBAL_IDENTIFIER_EXPRESSION_NODE;
}

std::string IRGlobalIdentifierExpressionNode::toString() {
    return "IR_GLOBAL_IDENTIFIER_EXPRESSION_NODE";
}

void IRGlobalIdentifierExpressionNode::print(std::unique_ptr<llvm::raw_fd_ostream> *stream) {
    _irValue->print(stream);
}