//
// Created by Johny Georges on 2025-03-29.
//

#include "ir-sref-expression-node.h"
#include "../../../shared/utils/logger/logger.h"

IRSrefExpressionNode::IRSrefExpressionNode(ASTSrefExpressionNode* node, IRExpressionNode* irExpression, IRPointerType* irType, IRInstructionNode* irValue) {
    _node = node;
    _irExpression = irExpression;
    _irType = irType;
    _irValue = irValue;
}

void IRSrefExpressionNode::markAsGlobal() {
    _isGlobal = true;
    _irExpression->markAsGlobal();
}

IRExpressionNode* IRSrefExpressionNode::getExpression() {
    return _irExpression;
}

IRInstructionNode* IRSrefExpressionNode::getIRValue() {
    return _irValue;
}

IRPointerType* IRSrefExpressionNode::getIRType() {
    return _irType;
}

TypeSignature* IRSrefExpressionNode::getTypeSignature() {
    return _node->getTypeSignature();
}

std::optional<IRInstructionNode*> IRSrefExpressionNode::getSourceAllocation() {
    return _irValue;
}

llvm::Value* IRSrefExpressionNode::getValue() {
    return _irExpression->getValue();
}

IRNodeType IRSrefExpressionNode::getNodeType() {
    return IR_SREF_EXPRESSION_NODE;
}

std::string IRSrefExpressionNode::toString() {
    return "IR_SREF_EXPRESSION_NODE";
}

void IRSrefExpressionNode::print(std::unique_ptr<llvm::raw_fd_ostream> *stream) {
    _irExpression->print(stream);
}