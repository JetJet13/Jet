//
// Created by Johny Georges on 2025-07-04.
//

#include "ir-interface-type-declaration-node.h"

IRInterfaceTypeDeclarationNode::IRInterfaceTypeDeclarationNode(std::shared_ptr<ASTInterfaceTypeDeclarationNode> node, IRStructType* irInterfaceType) {
    _node = node;
    _irInterfaceType = irInterfaceType;
}

std::string IRInterfaceTypeDeclarationNode::getName() {
    return _node->getName()->getId();
}

IRStructType* IRInterfaceTypeDeclarationNode::getIRType() {
    return _irInterfaceType;
}

IRNodeType IRInterfaceTypeDeclarationNode::getNodeType() {
    return IR_INTERFACE_TYPE_DECLARATION_NODE;
}

std::string IRInterfaceTypeDeclarationNode::toString() {
    return "IR_INTERFACE_TYPE_DECLARATION_NODE";
}

void IRInterfaceTypeDeclarationNode::print(std::unique_ptr<llvm::raw_fd_ostream> *stream) {
    _irInterfaceType->print();
}