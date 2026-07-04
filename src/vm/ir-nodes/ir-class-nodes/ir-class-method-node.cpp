//
// Created by Johny Georges on 2024-12-09.
//

#include "ir-class-method-node.h"

IRClassMethodNode::IRClassMethodNode(std::shared_ptr<ASTClassMethodDeclarationNode> node, llvm::Function* irValue, IRFunctionParameterListNode* irParameters, IRBlockNode* irBlock) {
    _node = node;
    _irValue = irValue;
    _irParameters = irParameters;
    _irBlock = irBlock;
}

std::shared_ptr<ASTClassMethodDeclarationNode> IRClassMethodNode::getNode() {
    return _node;
}

llvm::Function* IRClassMethodNode::getFunction() {
    return _irValue;
}

IRFunctionParameterListNode* IRClassMethodNode::getParameters() {
    return _irParameters;
}

IRBlockNode* IRClassMethodNode::getBlock() {
    return _irBlock;
}