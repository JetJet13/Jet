//
// Created by Johny Georges on 2025-03-19.
//

#include "ir-dref-expression-node.h"
#include "../../../shared/utils/logger/logger.h"

IRDrefExpressionNode::IRDrefExpressionNode(ASTDrefExpressionNode* node, IRExpressionNode* irExpression, IRType* irType, IRInstructionNode* irValue) {
    _node = node;
    _irExpression = irExpression;
    _irType = irType;
    _irValue = irValue;
}

void IRDrefExpressionNode::markAsGlobal() {
    _isGlobal = true;
    _irExpression->markAsGlobal();
}

bool IRDrefExpressionNode::isReferenced() {
    return _node->isReferenced();
}

IRExpressionNode* IRDrefExpressionNode::getExpression() {
    return _irExpression;
}

IRInstructionNode* IRDrefExpressionNode::getIRValue() {
    return _irValue;
}

IRType* IRDrefExpressionNode::getIRType() {
    return _irType;
}

TypeSignature* IRDrefExpressionNode::getTypeSignature() {
    return _node->getTypeSignature();
}

llvm::Value* IRDrefExpressionNode::getValue() {
    return _irExpression->getValue();
}

IRNodeType IRDrefExpressionNode::getNodeType() {
    return IR_DREF_EXPRESSION_NODE;
}

std::string IRDrefExpressionNode::toString() {
    return "IR_DREF_EXPRESSION_NODE";
}

void IRDrefExpressionNode::print(std::unique_ptr<llvm::raw_fd_ostream> *stream) {
    _irExpression->print(stream);
}