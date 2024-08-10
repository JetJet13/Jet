//
// Created by Johny Georges on 2024-07-01.
//

#include "ir-array-expression-node.h"

IRArrayExpressionNode::IRArrayExpressionNode(ASTArrayExpressionNode* node, IRInstructionNode* irValue, std::vector<IRExpressionNode*> irValues, IRArrayNode* array, IRType* type) {
    _node = node;
    _irValue = irValue;
    _irValues = irValues;
    _array = array;
    _type = type;
}

llvm::Value* IRArrayExpressionNode::insertSelfIntoBlock(std::unique_ptr<llvm::IRBuilder<>>*  builder) {
    auto arrayExpressionAllocation = builder->get()->Insert(_irValue->getValue());
    auto numElements = _irValues.size();
    auto zeroIndex = builder->get()->getInt32(0);
    for (int i = 0; i < numElements; ++i) {
        auto irExpression = _irValues[i];
        auto irIndex = builder->get()->getInt32(i);
        auto pointer = builder->get()->CreateInBoundsGEP(arrayExpressionAllocation->getType(), arrayExpressionAllocation, { zeroIndex, irIndex });
        auto irExpressionValue = irExpression->insertSelfIntoBlock(builder);
        builder->get()->CreateStore(irExpressionValue, pointer);
    }
    return _array->insertSelfIntoBlock(builder, _irValue);
}

llvm::Value* IRArrayExpressionNode::getValue() {
    return _irValue->getValue();
}

std::optional<IRInstructionNode*> IRArrayExpressionNode::getSourceAllocation() {
    return _irValue;
}

IRType* IRArrayExpressionNode::getIRType() {
    return _type;
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