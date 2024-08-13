//
// Created by Johny Georges on 2024-07-15.
//

#include "ir-enum-declaration-node.h"

IREnumDeclarationNode::IREnumDeclarationNode(ASTEnumDeclarationNode* node, IRGlobalVariableNode* irValue) {
    _node = node;
    _irValue = irValue;
}

void
IREnumDeclarationNode::insertSelfIntoBlock(std::unique_ptr<llvm::IRBuilder<>> *builder, IRInjectorMap *injectorMap) {}

IRNodeType IREnumDeclarationNode::getNodeType() {
    return IR_ENUM_DECLARATION_NODE;
}

std::string IREnumDeclarationNode::toString() {
    return "IR_ENUM_DECLARATION_NODE";
}

void IREnumDeclarationNode::print(std::unique_ptr<llvm::raw_fd_ostream> *stream) {
    _irValue->print(stream);
}