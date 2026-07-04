//
// Created by Johny Georges on 2024-12-09.
//

#include "ir-class-constructor-node.h"

IRClassConstructorNode::IRClassConstructorNode(std::shared_ptr<ASTClassConstructorDeclarationNode> node, llvm::Function* irValue, IRFunctionParameterListNode* irParameters, IRBlockNode* irBlock) {
    _node = node;
    _irValue = irValue;
    _irParameters = irParameters;
    _irBlock = irBlock;
}

std::shared_ptr<ASTClassConstructorDeclarationNode> IRClassConstructorNode::getNode() {
    return _node;
}

llvm::Function* IRClassConstructorNode::getFunction() {
    return _irValue;
}

IRFunctionParameterListNode* IRClassConstructorNode::getParameters() {
    return _irParameters;
}

IRBlockNode* IRClassConstructorNode::getBlock() {
    return _irBlock;
}