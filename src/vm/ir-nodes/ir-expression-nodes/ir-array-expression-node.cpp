//
// Created by Johny Georges on 2024-07-01.
//

#include "ir-array-expression-node.h"

IRArrayExpressionNode::IRArrayExpressionNode(ASTArrayExpressionNode* astNode, llvm::Constant* irValue, std::vector<IRExpressionNode*> irValues) {
    _astNode = astNode;
    _irValue = irValue;
    _irValues = irValues;
}

llvm::Value* IRArrayExpressionNode::insertSelfIntoBlock(std::unique_ptr<llvm::IRBuilder<>>*  builder, llvm::Value *parent) {
    auto arrayExpressionAllocation = builder->get()->Insert(_irValue);
    auto numElements = _irValues.size();
    auto zeroIndex = builder->get()->getInt32(0);
    for (int i = 0; i < numElements; ++i) {
        auto irExpression = _irValues[i];
        auto irIndex = builder->get()->getInt32(i);
        auto pointer = builder->get()->CreateInBoundsGEP(arrayExpressionAllocation->getType(), arrayExpressionAllocation, { zeroIndex, irIndex });
        irExpression->insertSelfIntoBlock(builder, pointer);
    }
    builder->get()->CreateStore(arrayExpressionAllocation, parent);
    return arrayExpressionAllocation;
}

llvm::Constant* IRArrayExpressionNode::getIRValue() {
    return _irValue;
}

llvm::Type* IRArrayExpressionNode::getIRTypeAtIndex(unsigned long index) {
    return _irValue->getType()->getArrayElementType();
}

IRNodeType IRArrayExpressionNode::getNodeType() {
    return IR_ARRAY_EXPRESSION_NODE;
}

std::string IRArrayExpressionNode::toString() {
    return "IR_ARRAY_EXPRESSION_NODE";
}

void IRArrayExpressionNode::print(std::unique_ptr<llvm::raw_fd_ostream> *stream) {
    _irValue->print(**stream);
}