//
// Created by Johny Georges on 2024-07-01.
//

#include "ir-tuple-expression-node.h"

IRTupleExpressionNode::IRTupleExpressionNode(ASTTupleExpressionNode* node, IRInstructionNode* irValue, IRInstructionNode* irArc, IRStructRefType* type, std::vector<IRExpressionNode*> irValues) {
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

bool IRTupleExpressionNode::isReferenced() {
    return _node->isReferenced();
}

llvm::Value* IRTupleExpressionNode::getValue() {
    return _irValue->getValue();
}

unsigned long IRTupleExpressionNode::size() {
    return _irValues.size();
}

IRInstructionNode* IRTupleExpressionNode::getIRValue() {
    return _irValue;
}

std::vector<IRExpressionNode*>* IRTupleExpressionNode::getValues() {
    return &_irValues;
}

std::optional<IRInstructionNode*> IRTupleExpressionNode::getArc() {
    return _irArc;
}

IRStructRefType* IRTupleExpressionNode::getIRType() {
    return _type;
}

TypeSignature* IRTupleExpressionNode::getTypeSignature() {
    return _node->getTypeSignature();
}

Position* IRTupleExpressionNode::getStartPosition() {
    return _node->getStartPosition();
}

Position* IRTupleExpressionNode::getEndPosition() {
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