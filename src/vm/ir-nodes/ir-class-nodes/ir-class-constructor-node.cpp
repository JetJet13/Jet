//
// Created by Johny Georges on 2024-12-09.
//

#include "ir-class-constructor-node.h"

IRClassConstructorNode::IRClassConstructorNode(ASTClassConstructorDeclarationNode* node, llvm::Function* irValue, IRFunctionParameterListNode* irParameters, IRBlockNode* irBlock, IRLookupTable* scope) {
    _node = node;
    _irValue = irValue;
    _irParameters = irParameters;
    _irBlock = irBlock;
    _scope = scope;
}

ASTClassConstructorDeclarationNode* IRClassConstructorNode::getNode() {
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

IRLookupTable* IRClassConstructorNode::getScope() {
    return _scope;
}