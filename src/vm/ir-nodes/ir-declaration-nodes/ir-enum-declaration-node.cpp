//
// Created by Johny Georges on 2024-07-15.
//

#include "ir-enum-declaration-node.h"

IREnumDeclarationNode::IREnumDeclarationNode(std::shared_ptr<ASTEnumDeclarationNode> node, IRInstructionNode* irValue) {
    _node = node;
    _irValue = irValue;
}

llvm::Value* IREnumDeclarationNode::getValue() {
    return _irValue->getValue();
}

IRNodeType IREnumDeclarationNode::getNodeType() {
    return IR_ENUM_DECLARATION_NODE;
}

std::string IREnumDeclarationNode::toString() {
    return "IR_ENUM_DECLARATION_NODE";
}

void IREnumDeclarationNode::print(std::unique_ptr<llvm::raw_fd_ostream> *stream) {
    _irValue->print(stream);
}