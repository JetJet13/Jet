//
// Created by Johny Georges on 2024-12-09.
//

#include "ir-class-constructor-node.h"

IRClassConstructorNode::IRClassConstructorNode(std::shared_ptr<ASTClassConstructorDeclarationNode> node, llvm::Function* irValue, std::shared_ptr<IRFunctionParameterListNode> irParameters, std::shared_ptr<IRBlockNode> irBlock) {
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

std::shared_ptr<IRFunctionParameterListNode> IRClassConstructorNode::getParameters() {
    return _irParameters;
}

std::shared_ptr<IRBlockNode> IRClassConstructorNode::getBlock() {
    return _irBlock;
}