//
// Created by Johny Georges on 2024-10-29.
//

#include "ir-module-declaration-node.h"

IRModuleDeclarationNode::IRModuleDeclarationNode(ASTModuleDeclarationNode* node) {
    _node = node;
}

IRNodeType IRModuleDeclarationNode::getNodeType() {
    return IR_MODULE_DECLARATION_NODE;
}

std::string IRModuleDeclarationNode::toString() {
    return "IR_MODULE_DECLARATION_NODE";
}

void IRModuleDeclarationNode::print(std::unique_ptr<llvm::raw_fd_ostream> *stream) {
}