//
// Created by Johny Georges on 2024-12-14.
//

#include "ir-class-property-access-expression-node.h"
#include "../../../shared/utils/logger/logger.h"
#include "../../ir-type/ir-struct-ref-type.h"

IRClassPropertyAccessExpressionNode::IRClassPropertyAccessExpressionNode(std::shared_ptr<ASTClassPropertyAccessExpressionNode> node, IRInstructionNode* irSource, std::string targetKey, unsigned long targetKeyIndex, llvm::Constant* irTargetKeyIndex, IRType* irType, std::optional<IRInstructionNode*> sourceAllocation) {
    _node = node;
    _irSource = irSource;
    _targetKey = targetKey;
    _irTargetKeyIndex = irTargetKeyIndex;
    _targetKeyIndex = targetKeyIndex;
    _irType = irType;
    _sourceAllocation = sourceAllocation;
}

std::shared_ptr<ASTClassPropertyAccessExpressionNode> IRClassPropertyAccessExpressionNode::getNode() {
    return _node;
}

IRInstructionNode* IRClassPropertyAccessExpressionNode::getSource() {
    return _irSource;
}

std::string* IRClassPropertyAccessExpressionNode::getTargetKey() {
    return &_targetKey;
}

llvm::Constant* IRClassPropertyAccessExpressionNode::getIRTargetKeyIndex() {
    return _irTargetKeyIndex;
}

unsigned long IRClassPropertyAccessExpressionNode::getTargetKeyIndex() {
    return _targetKeyIndex;
}

std::optional<IRInstructionNode*> IRClassPropertyAccessExpressionNode::getSourceAllocation() {
    return _sourceAllocation;
}

IRType* IRClassPropertyAccessExpressionNode::getIRType() {
    return _irType;
}

TypeSignature* IRClassPropertyAccessExpressionNode::getTypeSignature() {
    return _node->getTypeSignature();
}

Position* IRClassPropertyAccessExpressionNode::getStartPosition() {
    return _node->getStartPosition();
}

Position* IRClassPropertyAccessExpressionNode::getEndPosition() {
    return _node->getEndPosition();
}

IRType* IRClassPropertyAccessExpressionNode::getTargetIRType() {
    return ((IRStructRefType*)_irSource->getIRType()->getUnderlyingType())->getStructIRType()->getIRTypeForKey(_targetKey);
}

llvm::Value* IRClassPropertyAccessExpressionNode::getValue() {
    return _irSource->getValue();
}

IRNodeType IRClassPropertyAccessExpressionNode::getNodeType() {
    return IR_CLASS_PROPERTY_ACCESS_EXPRESSION_NODE;
}

std::string IRClassPropertyAccessExpressionNode::toString() {
    return "IR_CLASS_PROPERTY_ACCESS_EXPRESSION_NODE";
}

void IRClassPropertyAccessExpressionNode::print(std::unique_ptr<llvm::raw_fd_ostream> *stream) {
    _irSource->print(stream);
}