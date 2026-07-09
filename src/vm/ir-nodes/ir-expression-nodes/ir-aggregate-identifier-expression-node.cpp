//
// Created by Johny Georges on 2024-09-04.
//

#include "ir-aggregate-identifier-expression-node.h"

IRAggregateIdentifierExpressionNode::IRAggregateIdentifierExpressionNode(std::shared_ptr<ASTIdentifierExpressionNode> node, std::shared_ptr<IRInstructionNode> irAllocation, std::shared_ptr<IRInstructionNode> arrayPointerSourceAllocation, std::shared_ptr<IRInstructionNode> sourceAllocation, llvm::GetElementPtrInst* intPointer, llvm::LoadInst* loadedNumElements, std::shared_ptr<IRArrayPointerType> type) {
    _node = node;
    _arrayAllocation = irAllocation;
    _arrayPointerAllocation = arrayPointerSourceAllocation;
    _intPointer = intPointer;
    _loadedNumElements = loadedNumElements;
    _type = type;
    _sourceAllocation = sourceAllocation;
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


std::optional<std::shared_ptr<IRInstructionNode>> IRAggregateIdentifierExpressionNode::getSourceAllocation() {
    return _sourceAllocation;
}

std::shared_ptr<IRInstructionNode> IRAggregateIdentifierExpressionNode::getAggregateSourceAllocation() {
    if (!_sourceAllocation->getParentAllocation()) {
        throw std::logic_error("source allocation has no parent allocation");
    }
    if (_sourceAllocation->getParentAllocation().value()->getParentAllocation()) {
        return _sourceAllocation->getParentAllocation().value()->getParentAllocation().value();
    }
    return _sourceAllocation->getParentAllocation().value();
}

std::shared_ptr<IRInstructionNode> IRAggregateIdentifierExpressionNode::getAggregateAllocation() {
    return _arrayAllocation;
}

std::shared_ptr<IRInstructionNode> IRAggregateIdentifierExpressionNode::getAggregatePointerAllocation() {
    return _arrayPointerAllocation;
}

std::shared_ptr<IRType> IRAggregateIdentifierExpressionNode::getIRType() {
    return _type;
}

std::shared_ptr<TypeSignature> IRAggregateIdentifierExpressionNode::getTypeSignature() {
    return _node->getTypeSignature();
}

std::shared_ptr<Position> IRAggregateIdentifierExpressionNode::getStartPosition() {
    return _node->getStartPosition();
}

std::shared_ptr<Position> IRAggregateIdentifierExpressionNode::getEndPosition() {
    return _node->getEndPosition();
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