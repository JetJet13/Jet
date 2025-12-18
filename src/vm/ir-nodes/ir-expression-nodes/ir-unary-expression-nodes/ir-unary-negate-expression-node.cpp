//
// Created by Johny Georges on 2024-07-01.
//

#include "ir-unary-negate-expression-node.h"

IRUnaryNegateExpressionNode::IRUnaryNegateExpressionNode(ASTUnaryExpressionNode* node, IRExpressionNode* irExpression, IRType* type) {
    _node = node;
    _irExpression = irExpression;
    _type = type;
}

IRExpressionNode* IRUnaryNegateExpressionNode::getIRExpression() {
    return _irExpression;
}

bool IRUnaryNegateExpressionNode::isReferenced() {
    return _node->isReferenced();
}

void IRUnaryNegateExpressionNode::markAsGlobal() {
    _isGlobal = true;
    _irExpression->markAsGlobal();
}

llvm::Value* IRUnaryNegateExpressionNode::getValue() {
    return _irExpression->getValue();
}

IRType* IRUnaryNegateExpressionNode::getIRType() {
    return _type;
}

TypeSignature* IRUnaryNegateExpressionNode::getTypeSignature() {
    return _node->getTypeSignature();
}

Position* IRUnaryNegateExpressionNode::getStartPosition() {
    return _node->getStartPosition();
}

Position* IRUnaryNegateExpressionNode::getEndPosition() {
    return _node->getEndPosition();
}

IRNodeType IRUnaryNegateExpressionNode::getNodeType() {
    return IR_UNARY_NEGATE_EXPRESSION_NODE;
}

std::string IRUnaryNegateExpressionNode::toString() {
    return "IR_UNARY_NEGATE_EXPRESSION_NODE";
}

void IRUnaryNegateExpressionNode::print(std::unique_ptr<llvm::raw_fd_ostream> *stream) {
    _irExpression->print(stream);
}