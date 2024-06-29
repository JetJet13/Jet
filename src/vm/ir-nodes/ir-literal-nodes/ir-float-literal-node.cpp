//
// Created by Johny Georges on 2024-06-29.
//

#include "ir-float-literal-node.h"

IRFloatLiteralNode::IRFloatLiteralNode(ASTFloatLiteralNode* astFloatLiteralNode, llvm::ConstantFP* irValue) {
    _astNode = astFloatLiteralNode;
    _irValue = irValue;
}

llvm::ConstantFP* IRFloatLiteralNode::getIRValue() {
    return _irValue;
}

IRNodeType IRFloatLiteralNode::getNodeType() {
    return IR_FLOAT_LITERAL_NODE;
}

std::string IRFloatLiteralNode::toString() {
    return "IR_FLOAT_LITERAL_NODE";
}