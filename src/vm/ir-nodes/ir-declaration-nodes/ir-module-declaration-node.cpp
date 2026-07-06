//
// Created by Johny Georges on 2024-10-29.
//

#include "ir-module-declaration-node.h"

IRModuleDeclarationNode::IRModuleDeclarationNode(std::shared_ptr<ASTModuleDeclarationNode> node, std::shared_ptr<IRInstructionNode> allocation, std::shared_ptr<IRModuleType> type, std::vector<std::shared_ptr<IRDeclarationNode>> exports) {
    _node = node;
    _allocation = allocation;
    _type = type;
    _exports = exports;
}

std::shared_ptr<IRInstructionNode> IRModuleDeclarationNode::getAllocation() {
    return _allocation;
}

std::shared_ptr<IRModuleType> IRModuleDeclarationNode::getIRType() {
    return _type;
}

std::vector<std::shared_ptr<IRDeclarationNode>>* IRModuleDeclarationNode::getExports() {
    return &_exports;
}

llvm::Value* IRModuleDeclarationNode::getValue() {
    return _allocation->getValue();
}

IRNodeType IRModuleDeclarationNode::getNodeType() {
    return IR_MODULE_DECLARATION_NODE;
}

std::string IRModuleDeclarationNode::toString() {
    return "IR_MODULE_DECLARATION_NODE";
}

void IRModuleDeclarationNode::print(std::unique_ptr<llvm::raw_fd_ostream> *stream) {
    for (auto exportedNode : _exports) {
        exportedNode->print(stream);
    }
}