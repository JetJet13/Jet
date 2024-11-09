//
// Created by Johny Georges on 2024-07-01.
//

#include "ir-tuple-expression-node.h"

IRTupleExpressionNode::IRTupleExpressionNode(ASTTupleExpressionNode* node, IRInstructionNode* irValue, IRStructType* type, std::vector<IRExpressionNode*> irValues) {
    _node = node;
    _irValue = irValue;
    _irValues = irValues;
    _type = type;
}

llvm::Value* IRTupleExpressionNode::getValue() {
    return _irValue->getValue();
}

unsigned long IRTupleExpressionNode::size() {
    return _irValues.size();
}

std::vector<IRExpressionNode*>* IRTupleExpressionNode::getValues() {
    return &_irValues;
}

IRStructType* IRTupleExpressionNode::getIRType() {
    return _type;
}

TypeSignature* IRTupleExpressionNode::getTypeSignature() {
    return _node->getTypeSignature();
}

IRNodeType IRTupleExpressionNode::getNodeType() {
    return IR_TUPLE_EXPRESSION_NODE;
}

std::string IRTupleExpressionNode::toString() {
    return "IR_TUPLE_EXPRESSION_NODE";
}

void IRTupleExpressionNode::print(std::unique_ptr<llvm::raw_fd_ostream> *stream) {
    _irValue->print(stream);
}