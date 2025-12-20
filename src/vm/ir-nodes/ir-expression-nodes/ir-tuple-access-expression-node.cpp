//
// Created by Johny Georges on 2024-10-09.
//

#include "ir-tuple-access-expression-node.h"
#include "../../../shared/utils/logger/logger.h"
#include "../../ir-type/ir-struct-pointer-type.h"

IRTupleAccessExpressionNode::IRTupleAccessExpressionNode(ASTTupleAccessExpressionNode* node, IRExpressionNode* irSource, unsigned long targetKeyIndex, llvm::Constant* irTargetKeyIndex, IRType* irType, std::optional<IRInstructionNode*> sourceAllocation) {
    _node = node;
    _irSource = irSource;
    _irTargetKeyIndex = irTargetKeyIndex;
    _targetKeyIndex = targetKeyIndex;
    _irType = irType;
    _sourceAllocation = sourceAllocation;
}

void IRTupleAccessExpressionNode::markAsGlobal() {
    _isGlobal = true;
    _irSource->markAsGlobal();
}

bool IRTupleAccessExpressionNode::isReferenced() {
    return _node->isReferenced();
}

std::optional<IRInstructionNode*> IRTupleAccessExpressionNode::getSourceAllocation() {
    return _sourceAllocation;
}

IRExpressionNode* IRTupleAccessExpressionNode::getSource() {
    return _irSource;
}

llvm::Constant* IRTupleAccessExpressionNode::getIRTargetKeyIndex() {
    return _irTargetKeyIndex;
}

unsigned long IRTupleAccessExpressionNode::getTargetKeyIndex() {
    return _targetKeyIndex;
}

IRType* IRTupleAccessExpressionNode::getIRType() {
    return _irType;
}

TypeSignature* IRTupleAccessExpressionNode::getTypeSignature() {
    return _node->getTypeSignature();
}

Position* IRTupleAccessExpressionNode::getStartPosition() {
    return _node->getStartPosition();
}

Position* IRTupleAccessExpressionNode::getEndPosition() {
    return _node->getEndPosition();
}

IRType* IRTupleAccessExpressionNode::getTargetIRType() {
    return ((IRStructRefType*)_irSource->getUnderlyingIRType())->getStructIRType()->getIRTypeByIndex(_targetKeyIndex);
}

llvm::Value* IRTupleAccessExpressionNode::getValue() {
    return _irSource->getValue();
}

IRNodeType IRTupleAccessExpressionNode::getNodeType() {
    return IR_TUPLE_ACCESS_EXPRESSION_NODE;
}

std::string IRTupleAccessExpressionNode::toString() {
    return "IR_TUPLE_ACCESS_EXPRESSION_NODE";
}

void IRTupleAccessExpressionNode::print(std::unique_ptr<llvm::raw_fd_ostream> *stream) {
    _irSource->print(stream);
}