//
// Created by Johny Georges on 2024-07-01.
//

#include "ir-unary-negate-expression-node.h"

IRUnaryNegateExpressionNode::IRUnaryNegateExpressionNode(ASTUnaryExpressionNode* astNode, llvm::UnaryOperator* irValue, IRExpressionNode* irExpression) {
    _astNode = astNode;
    _irValue = irValue;
    _irExpression = irExpression;
}

llvm::Value * IRUnaryNegateExpressionNode::insertSelfIntoBlock(std::unique_ptr<llvm::IRBuilder<>>*  builder, llvm::Value *parent) {
    return builder->get()->CreateStore(builder->get()->Insert(_irValue), parent);
}

llvm::UnaryOperator* IRUnaryNegateExpressionNode::getIRValue() {
    return _irValue;
}

IRNodeType IRUnaryNegateExpressionNode::getNodeType() {
    return IR_UNARY_EXPRESSION_NODE;
}

std::string IRUnaryNegateExpressionNode::toString() {
    return "IR_UNARY_EXPRESSION_NODE";
}

void IRUnaryNegateExpressionNode::print(std::unique_ptr<llvm::raw_fd_ostream> *stream) {
    _irValue->print(**stream);
    stream->get()->write('\n');
    _irExpression->print(stream);
}