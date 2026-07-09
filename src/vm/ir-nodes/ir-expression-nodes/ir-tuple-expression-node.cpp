//
// Created by Johny Georges on 2024-07-01.
//

#include "ir-tuple-expression-node.h"

IRTupleExpressionNode::IRTupleExpressionNode(std::shared_ptr<ASTTupleExpressionNode> node, std::shared_ptr<IRInstructionNode> irValue, std::shared_ptr<IRInstructionNode> irArc, std::shared_ptr<IRStructRefType> type, std::vector<std::shared_ptr<IRExpressionNode>> irValues) {
    _node = node;
    _irValue = irValue;
    _irArc = irArc;
    _irValues = irValues;
    _type = type;
}

void IRTupleExpressionNode::markAsGlobal() {
    _isGlobal = true;
    for (auto irValue : _irValues) {
        irValue->markAsGlobal();
    }
}

llvm::Value* IRTupleExpressionNode::getValue() {
    return _irValue->getValue();
}

unsigned long IRTupleExpressionNode::size() {
    return _irValues.size();
}

std::shared_ptr<IRInstructionNode> IRTupleExpressionNode::getIRValue() {
    return _irValue;
}

std::vector<std::shared_ptr<IRExpressionNode>>* IRTupleExpressionNode::getValues() {
    return &_irValues;
}

std::optional<std::shared_ptr<IRInstructionNode>> IRTupleExpressionNode::getArc() {
    return _irArc;
}

std::shared_ptr<IRStructRefType> IRTupleExpressionNode::getIRStructRefType() {
    return _type;
}

std::shared_ptr<IRType> IRTupleExpressionNode::getIRType() {
    return _type;
}

std::shared_ptr<TypeSignature> IRTupleExpressionNode::getTypeSignature() {
    return _node->getTypeSignature();
}

std::shared_ptr<Position> IRTupleExpressionNode::getStartPosition() {
    return _node->getStartPosition();
}

std::shared_ptr<Position> IRTupleExpressionNode::getEndPosition() {
    return _node->getEndPosition();
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