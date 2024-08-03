//
// Created by Johny Georges on 2024-07-17.
//

#include "ir-global-identifier-expression-node.h"

IRGlobalIdentifierExpressionNode::IRGlobalIdentifierExpressionNode(ASTIdentifierExpressionNode* node, IRGlobalVariableNode* irValue) {
    _node = node;
    _irValue = irValue;
}

llvm::GlobalVariable* IRGlobalIdentifierExpressionNode::insertSelfIntoBlock(std::unique_ptr<llvm::IRBuilder<>>*  builder) {
    return _irValue->getValue();
}

llvm::GlobalVariable* IRGlobalIdentifierExpressionNode::getValue() {
    return _irValue->getValue();
}

IRInstructionNode* IRGlobalIdentifierExpressionNode::getSourceAllocation() {
    return _irValue->getSourceAllocation();
}

IRPointerType* IRGlobalIdentifierExpressionNode::getIRType() {
    return _irValue->getIRType();
}

llvm::Type* IRGlobalIdentifierExpressionNode::getType() {
    return _irValue->getValue()->getValueType();
}

llvm::Type* IRGlobalIdentifierExpressionNode::getTypeAtIndex(unsigned long index) {
    return _irValue->getIRType()->getPointerSourceIRType()->getType();
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