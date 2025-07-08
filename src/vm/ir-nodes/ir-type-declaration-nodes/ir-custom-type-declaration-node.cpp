//
// Created by Johny Georges on 2025-07-07.
//

#include "ir-custom-type-declaration-node.h"

IRCustomTypeDeclarationNode::IRCustomTypeDeclarationNode(ASTCustomTypeDeclarationNode* node, IRType* irType) {
    _node = node;
    _irType = irType;
}

std::string IRCustomTypeDeclarationNode::getName() {
    return _node->getName()->getId();
}

IRType* IRCustomTypeDeclarationNode::getIRType() {
    return _irType;
}

IRNodeType IRCustomTypeDeclarationNode::getNodeType() {
    return IR_CUSTOM_TYPE_DECLARATION_NODE;
}

std::string IRCustomTypeDeclarationNode::toString() {
    return "IR_CUSTOM_TYPE_DECLARATION_NODE";
}

void IRCustomTypeDeclarationNode::print(std::unique_ptr<llvm::raw_fd_ostream> *stream) {
    _irType->print();
}