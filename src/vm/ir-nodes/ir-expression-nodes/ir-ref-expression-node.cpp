//
// Created by Johny Georges on 2025-02-10.
//

#include "ir-ref-expression-node.h"

IRRefExpressionNode::IRRefExpressionNode(ASTRefExpressionNode* node, IRExpressionNode* irValue, IRPointerType* irType) {
    _node = node;
    _irExpression = irValue;
    _irType = irType;
}

void IRRefExpressionNode::markAsGlobal() {
    _isGlobal = true;
    _irExpression->markAsGlobal();
}

IRExpressionNode* IRRefExpressionNode::getExpression() {
    return _irExpression;
}

IRPointerType* IRRefExpressionNode::getIRType() {
    return _irType;
}

TypeSignature* IRRefExpressionNode::getTypeSignature() {
    return _node->getTypeSignature();
}

llvm::Value* IRRefExpressionNode::getValue() {
    return _irExpression->getValue();
}

IRNodeType IRRefExpressionNode::getNodeType() {
    return IR_REF_EXPRESSION_NODE;
}

std::string IRRefExpressionNode::toString() {
    return "IR_REF_EXPRESSION_NODE";
}

void IRRefExpressionNode::print(std::unique_ptr<llvm::raw_fd_ostream> *stream) {
    _irExpression->print(stream);
}