//
// Created by Johny Georges on 2024-07-16.
//

#include "ir-object-access-expression-node.h"
#include "../../../shared/utils/logger/logger.h"

IRObjectAccessExpressionNode::IRObjectAccessExpressionNode(ASTObjectAccessExpressionNode* node, IRExpressionNode* irSource, std::string targetKey, unsigned long targetKeyIndex, llvm::Constant* irTargetKeyIndex, IRType* irType, std::optional<IRInstructionNode*> sourceAllocation) {
    _node = node;
    _irSource = irSource;
    _targetKey = targetKey;
    _irTargetKeyIndex = irTargetKeyIndex;
    _targetKeyIndex = targetKeyIndex;
    _irType = irType;
    _sourceAllocation = sourceAllocation;
}

void IRObjectAccessExpressionNode::markAsGlobal() {
    _isGlobal = true;
    _irSource->markAsGlobal();
}

ASTObjectAccessExpressionNode* IRObjectAccessExpressionNode::getNode() {
    return _node;
}

std::optional<IRInstructionNode*> IRObjectAccessExpressionNode::getSourceAllocation() {
    return _sourceAllocation;
}

IRExpressionNode* IRObjectAccessExpressionNode::getSource() {
    return _irSource;
}

std::string* IRObjectAccessExpressionNode::getTargetKey() {
    return &_targetKey;
}

llvm::Constant* IRObjectAccessExpressionNode::getIRTargetKeyIndex() {
    return _irTargetKeyIndex;
}

unsigned long IRObjectAccessExpressionNode::getTargetKeyIndex() {
    return _targetKeyIndex;
}

IRType* IRObjectAccessExpressionNode::getIRType() {
    return _irType;
}

TypeSignature* IRObjectAccessExpressionNode::getTypeSignature() {
    return _node->getTypeSignature();
}

IRType* IRObjectAccessExpressionNode::getTargetIRType() {
    return ((IRStructType*)_irSource->getIRType()->getSourceType())->getIRTypeForKey(_targetKey);
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