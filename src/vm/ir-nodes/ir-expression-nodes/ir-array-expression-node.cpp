//
// Created by Johny Georges on 2024-07-01.
//

#include "ir-array-expression-node.h"
#include "../../ir-injector/ir-injector-map.h"

IRArrayExpressionNode::IRArrayExpressionNode(ASTArrayExpressionNode* node, IRInstructionNode* irValue, IRInstructionNode* arrayPointerSourceAllocation, std::vector<IRExpressionNode*> irValues, IRArrayPointerType* type) {
    _node = node;
    _irValue = irValue;
    _arrayPointerSourceAllocation = arrayPointerSourceAllocation;
    _irValues = irValues;
    _type = type;
}

llvm::Value* IRArrayExpressionNode::insertSelfIntoBlock(std::unique_ptr<llvm::IRBuilder<>> *builder, IRInjectorMap *injectorMap) {
    return injectorMap->getArrayInjector()->inject(this, builder);
}

llvm::Value* IRArrayExpressionNode::getValue() {
    return _irValue->getValue();
}

std::vector<IRExpressionNode*>* IRArrayExpressionNode::getValues() {
    return &_irValues;
}

std::optional<IRInstructionNode*> IRArrayExpressionNode::getSourceAllocation() {
    return _irValue;
}

IRInstructionNode* IRArrayExpressionNode::getSourceArrayAllocation() {
    return _irValue;
}

IRInstructionNode* IRArrayExpressionNode::getArrayPointerAllocation() {
    return _arrayPointerSourceAllocation;
}

IRArrayPointerType* IRArrayExpressionNode::getIRType() {
    return _type;
}

unsigned long IRArrayExpressionNode::size() {
    return _irValues.size();
}

llvm::Type* IRArrayExpressionNode::getTypeAtIndex(unsigned long index) {
    return _irValue->getIRType()->getSourceType()->getType()->getArrayElementType();
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