//
// Created by Johny Georges on 2024-07-02.
//

#include "ir-literal-expression-node.h"

IRLiteralExpressionNode::IRLiteralExpressionNode(ASTLiteralExpressionNode* astNode, IRLiteralNode* irValue) {
    _astNode = astNode;
    _irValue = irValue;
}

llvm::Constant* IRLiteralExpressionNode::getConstantIRValue() {
    return _irValue->getConstantIRValue();
}

llvm::Value* IRLiteralExpressionNode::getIRValue() {
    return _irValue->getIRValue();
}

IRNodeType IRLiteralExpressionNode::getNodeType() {
    return IR_LITERAL_EXPRESSION_NODE;
}

std::string IRLiteralExpressionNode::toString() {
    return "IR_LITERAL_EXPRESSION_NODE";
}