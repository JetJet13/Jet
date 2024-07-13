//
// Created by Johny Georges on 2024-07-01.
//

#include "ir-tuple-expression-node.h"

IRTupleExpressionNode::IRTupleExpressionNode(ASTTupleExpressionNode* node, llvm::Constant* irValue, std::vector<IRExpressionNode*> irValues) {
    _node = node;
    _irValue = irValue;
    _irValues = irValues;
}

llvm::Value * IRTupleExpressionNode::insertSelfIntoBlock(std::unique_ptr<llvm::IRBuilder<>>*  builder) {
    auto tupleExpressionAllocation = builder->get()->Insert(_irValue);
    auto numElements = _irValues.size();
    auto zeroIndex = builder->get()->getInt32(0);
    for (int i = 0; i < numElements; ++i) {
        auto irExpression = _irValues[i];
        auto irIndex = builder->get()->getInt32(i);
        auto pointer = builder->get()->CreateInBoundsGEP(tupleExpressionAllocation->getType(), tupleExpressionAllocation, { zeroIndex, irIndex });
        auto irExpressionValue = irExpression->insertSelfIntoBlock(builder);
        builder->get()->CreateStore(irExpressionValue, pointer);
    }
    return tupleExpressionAllocation;
}

llvm::Constant* IRTupleExpressionNode::getIRValue() {
    return _irValue;
}

IRNodeType IRTupleExpressionNode::getNodeType() {
    return IR_TUPLE_EXPRESSION_NODE;
}

std::string IRTupleExpressionNode::toString() {
    return "IR_TUPLE_EXPRESSION_NODE";
}

void IRTupleExpressionNode::print(std::unique_ptr<llvm::raw_fd_ostream> *stream) {
    _irValue->print(**stream);
}