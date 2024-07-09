//
// Created by Johny Georges on 2024-06-29.
//

#include "ir-int-literal-node.h"

IRIntLiteralNode::IRIntLiteralNode(ASTIntLiteralNode* astNode, llvm::ConstantInt* irValue) {
    _astNode = astNode;
    _irValue = irValue;
}

llvm::ConstantInt* IRIntLiteralNode::getConstantIRValue() {
    return _irValue;
}

IRNodeType IRIntLiteralNode::getNodeType() {
    return IR_INT_LITERAL_NODE;
}

std::string IRIntLiteralNode::toString() {
    return "IR_INT_LITERAL_NODE";
}

void IRIntLiteralNode::print(std::unique_ptr<llvm::raw_fd_ostream> *stream) {
    _irValue->print(**stream);
}