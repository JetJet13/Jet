//
// Created by Johny Georges on 2024-07-01.
//

#include "ir-array-expression-node.h"

IRArrayExpressionNode::IRArrayExpressionNode(std::shared_ptr<ASTArrayExpressionNode> node, IRInstructionNode* irValue, IRInstructionNode* arrayPointerSourceAllocation, std::vector<IRExpressionNode*> irValues, IRArrayPointerType* type) {
    _node = node;
    _irValue = irValue;
    _arrayPointerSourceAllocation = arrayPointerSourceAllocation;
    _irValues = irValues;
    _type = type;
}

void IRArrayExpressionNode::markAsGlobal() {
    _isGlobal = true;
    for (auto irElement : _irValues) {
        irElement->markAsGlobal();
    }
}

llvm::Value* IRArrayExpressionNode::getValue() {
    return _irValue->getValue();
}

std::vector<IRExpressionNode*>* IRArrayExpressionNode::getValues() {
    return &_irValues;
}

std::optional<IRInstructionNode*> IRArrayExpressionNode::getSourceAllocation() {
    return _arrayPointerSourceAllocation;
}

IRInstructionNode* IRArrayExpressionNode::getSourceAggregateAllocation() {
    return _irValue;
}

IRInstructionNode* IRArrayExpressionNode::getAggregatePointerAllocation() {
    return _arrayPointerSourceAllocation;
}

IRArrayPointerType* IRArrayExpressionNode::getIRType() {
    return _type;
}

std::shared_ptr<TypeSignature> IRArrayExpressionNode::getTypeSignature() {
    return _node->getTypeSignature();
}

Position* IRArrayExpressionNode::getStartPosition() {
    return _node->getStartPosition();
}

Position* IRArrayExpressionNode::getEndPosition() {
    return _node->getEndPosition();
}

unsigned long IRArrayExpressionNode::size() {
    return _irValues.size();
}

llvm::Type* IRArrayExpressionNode::getTypeAtIndex(unsigned long index) {
    return _irValue->getIRType()->getUnderlyingType()->getType()->getArrayElementType();
}

IRNodeType IRArrayExpressionNode::getNodeType() {
    return IR_ARRAY_EXPRESSION_NODE;
}

std::string IRArrayExpressionNode::toString() {
    return "IR_ARRAY_EXPRESSION_NODE";
}

void IRArrayExpressionNode::print(std::unique_ptr<llvm::raw_fd_ostream> *stream) {
    _irValue->print(stream);
}