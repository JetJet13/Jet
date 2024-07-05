//
// Created by Johny Georges on 2024-06-29.
//

#include "ir-float-literal-node.h"

IRFloatLiteralNode::IRFloatLiteralNode(ASTFloatLiteralNode* astNode, llvm::ConstantFP* irValue) {
    _astNode = astNode;
    _irValue = irValue;
}

llvm::Constant* IRFloatLiteralNode::getConstantIRValue() {
    return _irValue;
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

void IRFloatLiteralNode::print(std::unique_ptr<llvm::raw_fd_ostream> *stream) {
    _irValue->print(**stream);
}