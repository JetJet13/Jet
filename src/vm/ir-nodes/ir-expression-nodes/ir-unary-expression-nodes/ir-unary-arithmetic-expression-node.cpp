//
// Created by Johny Georges on 2024-07-01.
//

#include "ir-unary-arithmetic-expression-node.h"

IRUnaryArithmeticExpressionNode::IRUnaryArithmeticExpressionNode(ASTUnaryExpressionNode* astNode, llvm::BinaryOperator* irValue, IRExpressionNode* irExpression) {
    _astNode = astNode;
    _irValue = irValue;
    _irExpression = irExpression;
}

llvm::Value * IRUnaryArithmeticExpressionNode::insertSelfIntoBlock(std::unique_ptr<llvm::IRBuilder<>>*  builder, llvm::Value *parent) {
    return builder->get()->CreateStore(builder->get()->Insert(_irValue), parent);
}

llvm::BinaryOperator* IRUnaryArithmeticExpressionNode::getIRValue() {
    return _irValue;
}

IRNodeType IRUnaryArithmeticExpressionNode::getNodeType() {
    return IR_UNARY_ARITHMETIC_EXPRESSION_NODE;
}

std::string IRUnaryArithmeticExpressionNode::toString() {
    return "IR_UNARY_EXPRESSION_NODE";
}

void IRUnaryArithmeticExpressionNode::print(std::unique_ptr<llvm::raw_fd_ostream> *stream) {
    _irValue->print(**stream);
    stream->get()->write('\n');
    _irExpression->print(stream);
}