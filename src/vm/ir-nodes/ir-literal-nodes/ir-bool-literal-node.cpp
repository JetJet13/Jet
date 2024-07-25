//
// Created by Johny Georges on 2024-06-29.
//

#include "ir-bool-literal-node.h"

IRBoolLiteralNode::IRBoolLiteralNode(ASTBooleanLiteralNode* astNode, llvm::ConstantInt* irValue) {
    _astNode = astNode;
    _irValue = irValue;
    _type = new IRType(_irValue->getType());
}

llvm::ConstantInt* IRBoolLiteralNode::getConstantIRValue() {
    return _irValue;
}

IRType* IRBoolLiteralNode::getIRType() {
    return _type;
}

IRNodeType IRBoolLiteralNode::getNodeType() {
    return IR_BOOL_LITERAL_NODE;
}

std::string IRBoolLiteralNode::toString() {
    return "IR_BOOL_LITERAL_NODE";
}

void IRBoolLiteralNode::print(std::unique_ptr<llvm::raw_fd_ostream> *stream) {
    _irValue->print(**stream);
}