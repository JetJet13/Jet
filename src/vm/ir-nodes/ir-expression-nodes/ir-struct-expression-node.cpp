//
// Created by Johny Georges on 2024-07-01.
//

#include "ir-struct-expression-node.h"

IRStructExpressionNode::IRStructExpressionNode(ASTStructExpressionNode* astNode, IRInstructionNode* irValue, IRStructType* type, std::vector<IRExpressionNode*> irValues) {
    _node = astNode;
    _irValue = irValue;
    _irValues = irValues;
    _type = type;
}

void IRStructExpressionNode::markAsGlobal() {
    _isGlobal = true;
    for (auto irValue : _irValues) {
        irValue->markAsGlobal();
    }
}

bool IRStructExpressionNode::isReferenced() {
    return _node->isReferenced();
}

IRStructType* IRStructExpressionNode::getIRType() {
    return _type;
}

TypeSignature* IRStructExpressionNode::getTypeSignature() {
    return _node->getTypeSignature();
}

std::optional<IRInstructionNode*> IRStructExpressionNode::getSourceAllocation() {
    return _irValue;
}

unsigned long IRStructExpressionNode::size() {
    return _irValues.size();
}

llvm::Value* IRStructExpressionNode::getValue() {
    return _irValue->getValue();
}

IRInstructionNode* IRStructExpressionNode::getIRValue() {
    return _irValue;
}

std::vector<IRExpressionNode*>* IRStructExpressionNode::getValues() {
    return &_irValues;
}

IRNodeType IRStructExpressionNode::getNodeType() {
    return IR_STRUCT_EXPRESSION_NODE;
}

std::string IRStructExpressionNode::toString() {
    return "IR_STRUCT_EXPRESSION_NODE";
}

void IRStructExpressionNode::print(std::unique_ptr<llvm::raw_fd_ostream> *stream) {
    _irValue->print(stream);
}