//
// Created by Johny Georges on 2024-12-09.
//

#include "ir-class-method-node.h"

IRClassMethodNode::IRClassMethodNode(std::shared_ptr<ASTClassMethodDeclarationNode> node, llvm::Function* irValue, std::shared_ptr<IRFunctionParameterListNode> irParameters, std::shared_ptr<IRBlockNode> irBlock, std::shared_ptr<IRInstructionNode> globalVariable) {
    _node = node;
    _irValue = irValue;
    _irParameters = irParameters;
    _irBlock = irBlock;
    _globalVariable = globalVariable;
}

std::shared_ptr<ASTClassMethodDeclarationNode> IRClassMethodNode::getNode() {
    return _node;
}

llvm::Function* IRClassMethodNode::getFunction() {
    return _irValue;
}

std::shared_ptr<IRFunctionParameterListNode> IRClassMethodNode::getParameters() {
    return _irParameters;
}

std::shared_ptr<IRInstructionNode> IRClassMethodNode::getGlobalVariable() {
    return _globalVariable;
}

std::shared_ptr<IRBlockNode> IRClassMethodNode::getBlock() {
    return _irBlock;
}