//
// Created by Johny Georges on 2024-07-02.
//

#include "ir-literal-expression-node.h"

IRLiteralExpressionNode::IRLiteralExpressionNode(std::shared_ptr<ASTLiteralExpressionNode> node, std::shared_ptr<IRLiteralNode> irValue, std::shared_ptr<IRType> irType) {
    _node = node;
    _irValue = irValue;
    _irType = irType;
}

std::shared_ptr<IRType> IRLiteralExpressionNode::getIRType() {
    return _irType;
}

std::shared_ptr<TypeSignature> IRLiteralExpressionNode::getTypeSignature() {
    return _node->getTypeSignature();
}

Position* IRLiteralExpressionNode::getStartPosition() {
    return _node->getStartPosition();
}

Position* IRLiteralExpressionNode::getEndPosition() {
    return _node->getEndPosition();
}

llvm::Constant* IRLiteralExpressionNode::getValue() {
    return _irValue->getConstantIRValue();
}

IRNodeType IRLiteralExpressionNode::getNodeType() {
    return IR_LITERAL_EXPRESSION_NODE;
}

std::string IRLiteralExpressionNode::toString() {
    return "IR_LITERAL_EXPRESSION_NODE";
}

void IRLiteralExpressionNode::print(std::unique_ptr<llvm::raw_fd_ostream> *stream) {
    _irValue->print(stream);
}