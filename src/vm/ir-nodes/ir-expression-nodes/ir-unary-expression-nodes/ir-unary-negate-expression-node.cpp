//
// Created by Johny Georges on 2024-07-01.
//

#include "ir-unary-negate-expression-node.h"

IRUnaryNegateExpressionNode::IRUnaryNegateExpressionNode(ASTUnaryExpressionNode* node, llvm::UnaryOperator* irValue, IRExpressionNode* irExpression, IRType* type) {
    _node = node;
    _irValue = irValue;
    _irExpression = irExpression;
    _type = type;
}

llvm::Value* IRUnaryNegateExpressionNode::insertSelfIntoBlock(std::unique_ptr<llvm::IRBuilder<>>*  builder) {
    return builder->get()->Insert(_irValue);
}

llvm::UnaryOperator* IRUnaryNegateExpressionNode::getValue() {
    return _irValue;
}

IRType* IRUnaryNegateExpressionNode::getIRType() {
    return _type;
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