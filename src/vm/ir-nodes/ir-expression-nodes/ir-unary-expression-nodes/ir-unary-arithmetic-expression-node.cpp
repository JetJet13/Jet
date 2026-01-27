//
// Created by Johny Georges on 2024-07-01.
//

#include "ir-unary-arithmetic-expression-node.h"

IRUnaryArithmeticExpressionNode::IRUnaryArithmeticExpressionNode(ASTUnaryExpressionNode* astNode, llvm::Value* irValue, IRExpressionNode* irExpression, IRType* type) {
    _node = astNode;
    _irValue = irValue;
    _irExpression = irExpression;
    _type = type;
}

IRExpressionNode* IRUnaryArithmeticExpressionNode::getIRValue() {
    return _irExpression;
}

void IRUnaryArithmeticExpressionNode::markAsGlobal() {
    _isGlobal = true;
    _irExpression->markAsGlobal();
}

bool IRUnaryArithmeticExpressionNode::isReferenced() {
    return _node->isReferenced();
}

llvm::Value* IRUnaryArithmeticExpressionNode::getValue() {
    return _irValue;
}

IRType* IRUnaryArithmeticExpressionNode::getIRType() {
    return _type;
}

TypeSignature* IRUnaryArithmeticExpressionNode::getTypeSignature() {
    return _node->getTypeSignature();
}

Position* IRUnaryArithmeticExpressionNode::getStartPosition() {
    return _node->getStartPosition();
}

Position* IRUnaryArithmeticExpressionNode::getEndPosition() {
    return _node->getEndPosition();
}

IRNodeType IRUnaryArithmeticExpressionNode::getNodeType() {
    return IR_UNARY_ARITHMETIC_EXPRESSION_NODE;
}

std::string IRUnaryArithmeticExpressionNode::toString() {
    return "IR_UNARY_ARITHMETIC_EXPRESSION_NODE";
}

void IRUnaryArithmeticExpressionNode::print(std::unique_ptr<llvm::raw_fd_ostream> *stream) {
    _irValue->print(**stream);
    stream->get()->write('\n');
    _irExpression->print(stream);
}