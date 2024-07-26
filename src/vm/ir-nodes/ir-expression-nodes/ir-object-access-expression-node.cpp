//
// Created by Johny Georges on 2024-07-16.
//

#include "ir-object-access-expression-node.h"

IRObjectAccessExpressionNode::IRObjectAccessExpressionNode(ASTObjectAccessExpressionNode* node, IRExpressionNode* irSource, std::string targetKey) {
    _node = node;
    _irSource = irSource;
    _targetKey = targetKey;
}

llvm::Value* IRObjectAccessExpressionNode::insertSelfIntoBlock(std::unique_ptr<llvm::IRBuilder<>>*  builder) {
    auto sourceValue = builder->get()->CreateLoad(_irSource->getIRType()->getType(), _irSource->getValue());
    auto sourcePointer = builder->get()->CreateInBoundsGEP(_irSource->getTypeAtIndex(_targetKeyIndex), sourceValue, {builder->get()->getInt32(0), _irTargetKeyIndex });
    return builder->get()->CreateLoad(_irSource->getTypeAtIndex(_targetKeyIndex), sourcePointer);
}

IRType* IRObjectAccessExpressionNode::getIRType() {
    return _irSource->getIRType();
}

llvm::Value* IRObjectAccessExpressionNode::getValue() {
    return _irSource->getValue();
}

IRNodeType IRObjectAccessExpressionNode::getNodeType() {
    return IR_OBJECT_ACCESS_EXPRESSION_NODE;
}

std::string IRObjectAccessExpressionNode::toString() {
    return "IR_OBJECT_ACCESS_EXPRESSION_NODE";
}

void IRObjectAccessExpressionNode::print(std::unique_ptr<llvm::raw_fd_ostream> *stream) {
    _irSource->print(stream);
}