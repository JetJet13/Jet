//
// Created by Johny Georges on 2024-06-29.
//

#include "ir-bool-literal-node.h"

IRBoolLiteralNode::IRBoolLiteralNode(ASTBooleanLiteralNode* astLiteralBoolNode, llvm::ConstantInt* irValue) {
    _astNode = astLiteralBoolNode;
    _irValue = irValue;
}

llvm::ConstantInt* IRBoolLiteralNode::getIRValue() {
    return _irValue;
}

IRNodeType IRBoolLiteralNode::getNodeType() {
    return IR_BOOL_LITERAL_NODE;
}

std::string IRBoolLiteralNode::toString() {
    return "IR_BOOL_LITERAL_NODE";
}