//
// Created by Johny Georges on 2024-12-09.
//

#include "ir-class-method-node.h"

IRClassMethodNode::IRClassMethodNode(ASTClassMethodDeclarationNode* node, llvm::Function* irValue, IRFunctionParameterListNode* irParameters, IRBlockNode* irBlock, IRLookupTable* scope) {
    _node = node;
    _irValue = irValue;
    _irParameters = irParameters;
    _irBlock = irBlock;
    _scope = scope;
}

ASTClassMethodDeclarationNode* IRClassMethodNode::getNode() {
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

IRLookupTable* IRClassMethodNode::getScope() {
    return _scope;
}