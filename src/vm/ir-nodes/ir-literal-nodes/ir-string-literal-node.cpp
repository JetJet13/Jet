//
// Created by Johny Georges on 2024-06-29.
//

#include "ir-string-literal-node.h"

IRStringLiteralNode::IRStringLiteralNode(ASTStringLiteralNode* astNode, llvm::Constant* irValue, IRArrayNode* irArray) {
    _astNode = astNode;
    _irValue = irValue;
    _irArray = irArray;
    _type = _irArray->getIRType();
}

IRArrayNode* IRStringLiteralNode::getIRArray() {
    return _irArray;
}

llvm::Constant* IRStringLiteralNode::getConstantIRValue() {
    return _irValue;
}

IRType* IRStringLiteralNode::getIRType() {
    return _type;
}

IRNodeType IRStringLiteralNode::getNodeType() {
    return IR_STRING_LITERAL_NODE;
}

std::string IRStringLiteralNode::toString() {
    return "IR_STRING_LITERAL_NODE";
}

void IRStringLiteralNode::print(std::unique_ptr<llvm::raw_fd_ostream> *stream) {
    _irValue->print(**stream);
}