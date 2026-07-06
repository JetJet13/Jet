//
// Created by Johny Georges on 2024-07-01.
//

#include "ir-unary-arithmetic-expression-node.h"

IRUnaryArithmeticExpressionNode::IRUnaryArithmeticExpressionNode(std::shared_ptr<ASTUnaryExpressionNode> astNode, llvm::BinaryOperator* irValue, std::shared_ptr<IRExpressionNode> irExpression, std::shared_ptr<IRType> type) {
    _node = astNode;
    _irValue = irValue;
    _irExpression = irExpression;
    _type = type;
}

std::shared_ptr<IRExpressionNode> IRUnaryArithmeticExpressionNode::getIRValue() {
    return _irExpression;
}

void IRUnaryArithmeticExpressionNode::markAsGlobal() {
    _isGlobal = true;
    _irExpression->markAsGlobal();
}

llvm::BinaryOperator* IRUnaryArithmeticExpressionNode::getValue() {
    return _irValue;
}

std::shared_ptr<IRType> IRUnaryArithmeticExpressionNode::getIRType() {
    return _type;
}

std::shared_ptr<TypeSignature> IRUnaryArithmeticExpressionNode::getTypeSignature() {
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