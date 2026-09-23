//
// Created by Johny Georges on 2024-07-16.
//

#include "ir-object-access-expression-node.h"
#include "../../../shared/utils/logger/logger.h"
#include "../../ir-type/ir-new-class-instance-type.h"
#include "../../ir-type/ir-class-instance-type.h"

IRObjectAccessExpressionNode::IRObjectAccessExpressionNode(std::shared_ptr<ASTObjectAccessExpressionNode> node, std::shared_ptr<IRExpressionNode> irSource, std::string targetKey, uint64_t targetKeyIndex, llvm::Constant* irTargetKeyIndex, std::shared_ptr<IRType> irType, std::optional<std::shared_ptr<IRInstructionNode>> sourceAllocation) {
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

std::shared_ptr<ASTObjectAccessExpressionNode> IRObjectAccessExpressionNode::getNode() {
    return _node;
}

std::optional<std::shared_ptr<IRInstructionNode>> IRObjectAccessExpressionNode::getSourceAllocation() {
    return _sourceAllocation;
}

std::optional<std::shared_ptr<IRInstructionNode>> IRObjectAccessExpressionNode::getArc() {
    return _irSource->getArc();
}

std::shared_ptr<IRExpressionNode> IRObjectAccessExpressionNode::getSource() {
    return _irSource;
}

std::string* IRObjectAccessExpressionNode::getTargetKey() {
    return &_targetKey;
}

llvm::Constant* IRObjectAccessExpressionNode::getIRTargetKeyIndex() {
    return _irTargetKeyIndex;
}

uint64_t IRObjectAccessExpressionNode::getTargetKeyIndex() {
    return _targetKeyIndex;
}

std::shared_ptr<IRType> IRObjectAccessExpressionNode::getIRType() {
    return _irType;
}

std::shared_ptr<TypeSignature> IRObjectAccessExpressionNode::getTypeSignature() {
    return _node->getTypeSignature();
}

std::shared_ptr<Position> IRObjectAccessExpressionNode::getStartPosition() {
    return _node->getStartPosition();
}

std::shared_ptr<Position> IRObjectAccessExpressionNode::getEndPosition() {
    return _node->getEndPosition();
}

std::shared_ptr<IRType> IRObjectAccessExpressionNode::getTargetIRType() {
    if (_irSource->getUnderlyingIRType()->isClassInstanceType()) {
        return std::dynamic_pointer_cast<IRClassInstanceType>(_irSource->getUnderlyingIRType())->getIRTypeForProperty(_targetKey);
    } else if (_irSource->getUnderlyingIRType()->isStructRefType()) {
        return std::dynamic_pointer_cast<IRStructRefType>(_irSource->getUnderlyingIRType())->getStructIRType()->getIRTypeForKey(_targetKey);
    }
    return std::dynamic_pointer_cast<IRStructType>(_irSource->getUnderlyingIRType())->getIRTypeForKey(_targetKey);
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