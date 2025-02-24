//
// Created by Johny Georges on 2025-02-24.
//

#include "ir-global-array-expression-node.h"

IRGlobalArrayExpressionNode::IRGlobalArrayExpressionNode(ASTArrayExpressionNode* node, IRInstructionNode* irValue, IRInstructionNode* arrayPointerSourceAllocation, std::vector<IRExpressionNode*> irValues, IRArrayPointerType* type) {
    _node = node;
    _irValue = irValue;
    _arrayPointerSourceAllocation = arrayPointerSourceAllocation;
    _irValues = irValues;
    _type = type;
}

void IRGlobalArrayExpressionNode::markAsGlobal() {
    _isGlobal = true;
    for (auto irElement : _irValues) {
        irElement->markAsGlobal();
    }
}

llvm::Value* IRGlobalArrayExpressionNode::getValue() {
    return _irValue->getValue();
}

std::vector<IRExpressionNode*>* IRGlobalArrayExpressionNode::getValues() {
    return &_irValues;
}

std::optional<IRInstructionNode*> IRGlobalArrayExpressionNode::getSourceAllocation() {
    return _arrayPointerSourceAllocation;
}

IRInstructionNode* IRGlobalArrayExpressionNode::getSourceAggregateAllocation() {
    return _irValue;
}

IRInstructionNode* IRGlobalArrayExpressionNode::getAggregatePointerAllocation() {
    return _arrayPointerSourceAllocation;
}

IRArrayPointerType* IRGlobalArrayExpressionNode::getIRType() {
    return _type;
}

TypeSignature* IRGlobalArrayExpressionNode::getTypeSignature() {
    return _node->getTypeSignature();
}

unsigned long IRGlobalArrayExpressionNode::size() {
    return _irValues.size();
}

llvm::Type* IRGlobalArrayExpressionNode::getTypeAtIndex(unsigned long index) {
    return _irValue->getIRType()->getSourceType()->getType()->getArrayElementType();
}

IRNodeType IRGlobalArrayExpressionNode::getNodeType() {
    return IR_GLOBAL_ARRAY_EXPRESSION_NODE;
}

std::string IRGlobalArrayExpressionNode::toString() {
    return "IR_GLOBAL_ARRAY_EXPRESSION_NODE";
}

void IRGlobalArrayExpressionNode::print(std::unique_ptr<llvm::raw_fd_ostream> *stream) {
    _irValue->print(stream);
}