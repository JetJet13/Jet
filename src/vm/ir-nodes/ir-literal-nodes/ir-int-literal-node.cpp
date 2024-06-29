//
// Created by Johny Georges on 2024-06-29.
//

#include "ir-int-literal-node.h"

IRIntLiteralNode::IRIntLiteralNode(ASTIntLiteralNode* astIntLiteralNode, llvm::ConstantInt* irValue) {
    _astNode = astIntLiteralNode;
    _irValue = irValue;
}

llvm::ConstantInt* IRIntLiteralNode::getIRValue() {
    return _irValue;
}

IRNodeType IRIntLiteralNode::getNodeType() {
    return IR_INT_LITERAL_NODE;
}

std::string IRIntLiteralNode::toString() {
    return "IR_INT_LITERAL_NODE";
}