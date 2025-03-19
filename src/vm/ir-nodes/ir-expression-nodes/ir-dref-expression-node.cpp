//
// Created by Johny Georges on 2025-03-19.
//

#include "ir-dref-expression-node.h"
#include "../../../shared/utils/logger/logger.h"

IRDrefExpressionNode::IRDrefExpressionNode(ASTDrefExpressionNode* node, IRExpressionNode* irValue, IRType* irType) {
    _node = node;
    _irExpression = irValue;
    _irType = irType;
}

void IRDrefExpressionNode::markAsGlobal() {
    _isGlobal = true;
    _irExpression->markAsGlobal();
}

IRExpressionNode* IRDrefExpressionNode::getExpression() {
    return _irExpression;
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