//
// Created by Johny Georges on 2024-07-01.
//

#include "ir-struct-expression-node.h"

IRStructExpressionNode::IRStructExpressionNode(ASTStructExpressionNode* astNode, llvm::Constant* irValue, std::vector<IRExpressionNode*> irValues) {
    _astNode = astNode;
    _irValue = irValue;
    _irValues = irValues;
}

llvm::Value * IRStructExpressionNode::insertSelfIntoBlock(std::unique_ptr<llvm::IRBuilder<>>*  builder) {
    auto structExpressionAllocation = builder->get()->Insert(_irValue);
    auto numElements = _irValues.size();
    auto zeroIndex = builder->get()->getInt32(0);
    for (int i = 0; i < numElements; ++i) {
        auto irExpression = _irValues[i];
        auto irIndex = builder->get()->getInt32(i);
        auto pointer = builder->get()->CreateInBoundsGEP(structExpressionAllocation->getType(), structExpressionAllocation, { zeroIndex, irIndex });
        auto irExpressionValue = irExpression->insertSelfIntoBlock(builder);
        builder->get()->CreateStore(irExpressionValue, pointer);
    }
    return structExpressionAllocation;
}

llvm::Constant* IRStructExpressionNode::getIRValue() {
    return _irValue;
}

IRNodeType IRStructExpressionNode::getNodeType() {
    return IR_STRUCT_EXPRESSION_NODE;
}

std::string IRStructExpressionNode::toString() {
    return "IR_STRUCT_EXPRESSION_NODE";
}

void IRStructExpressionNode::print(std::unique_ptr<llvm::raw_fd_ostream> *stream) {
    _irValue->print(**stream);
}