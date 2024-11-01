//
// Created by Johny Georges on 2024-10-30.
//

#include "ir-import-single-module-declaration-node.h"

IRImportSingleModuleDeclarationNode::IRImportSingleModuleDeclarationNode(ASTImportSingleModuleDeclarationNode* node) {
    _node = node;
}

llvm::Value* IRImportSingleModuleDeclarationNode::getValue() {
    // todo - fix;
    return nullptr;
}

IRNodeType IRImportSingleModuleDeclarationNode::getNodeType() {
    return IR_IMPORT_SINGLE_MODULE_DECLARATION_NODE;
}

std::string IRImportSingleModuleDeclarationNode::toString() {
    return "IR_IMPORT_SINGLE_MODULE_DECLARATION_NODE";
}

void IRImportSingleModuleDeclarationNode::print(std::unique_ptr<llvm::raw_fd_ostream> *stream) {
}