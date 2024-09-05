//
// Created by Johny Georges on 2024-09-04.
//

#include "ir-aggregate-identifier-expression-node.h"

IRAggregateIdentifierExpressionNode::IRAggregateIdentifierExpressionNode(ASTIdentifierExpressionNode* node, IRInstructionNode* irAllocation, IRInstructionNode* arrayPointerSourceAllocation, llvm::GetElementPtrInst* intPointer, llvm::LoadInst* loadedNumElements, IRArrayPointerType* type) {
    _node = node;
    _arrayAllocation = irAllocation;
    _arrayPointerSourceAllocation = arrayPointerSourceAllocation;
    _intPointer = intPointer;
    _loadedNumElements = loadedNumElements;
    _type = type;
}

llvm::GetElementPtrInst* IRAggregateIdentifierExpressionNode::getIntPointer() {
    return _intPointer;
}

llvm::LoadInst* IRAggregateIdentifierExpressionNode::getLoadedNumElements() {
    return _loadedNumElements;
}

llvm::Value* IRAggregateIdentifierExpressionNode::getValue() {
    return _arrayAllocation->getValue();
}


std::optional<IRInstructionNode*> IRAggregateIdentifierExpressionNode::getSourceAllocation() {
    return _arrayAllocation;
}

IRInstructionNode* IRAggregateIdentifierExpressionNode::getSourceAggregateAllocation() {
    return _arrayAllocation;
}

IRInstructionNode* IRAggregateIdentifierExpressionNode::getAggregatePointerAllocation() {
    return _arrayPointerSourceAllocation;
}

IRArrayPointerType* IRAggregateIdentifierExpressionNode::getIRType() {
    return _type;
}

TypeSignature* IRAggregateIdentifierExpressionNode::getTypeSignature() {
    return _node->getTypeSignature();
}

llvm::Type* IRAggregateIdentifierExpressionNode::getTypeAtIndex(unsigned long index) {
    return _arrayAllocation->getAllocatedType()->getArrayElementType();
}

IRNodeType IRAggregateIdentifierExpressionNode::getNodeType() {
    return IR_AGGREGATE_IDENTIFIER_EXPRESSION_NODE;
}

std::string IRAggregateIdentifierExpressionNode::toString() {
    return "IR_AGGREGATE_IDENTIFIER_EXPRESSION_NODE";
}

void IRAggregateIdentifierExpressionNode::print(std::unique_ptr<llvm::raw_fd_ostream> *stream) {
    _arrayAllocation->print(stream);
}