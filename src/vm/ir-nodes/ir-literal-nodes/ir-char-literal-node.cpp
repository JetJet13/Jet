//
// Created by Johny Georges on 2024-06-29.
//

#include "ir-char-literal-node.h"

IRCharLiteralNode::IRCharLiteralNode(std::shared_ptr<ASTCharLiteralNode> astNode, llvm::ConstantInt* irValue) {
    _astNode = astNode;
    _irValue = irValue;
    _type = std::make_shared<IRType>(_irValue->getType());
}

llvm::ConstantInt* IRCharLiteralNode::getConstantIRValue() {
    return _irValue;
}

std::shared_ptr<IRType> IRCharLiteralNode::getIRType() {
    return _type;
}

IRNodeType IRCharLiteralNode::getNodeType() {
    return IR_CHAR_LITERAL_NODE;
}

std::string IRCharLiteralNode::toString() {
    return "IR_CHAR_LITERAL_NODE";
}

void IRCharLiteralNode::print(std::unique_ptr<llvm::raw_fd_ostream> *stream) {
    _irValue->print(**stream);
}