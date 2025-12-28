//
// Created by Johny Georges on 2025-12-27.
//

#include "ir-class-pre-constructor-node.h"

IRClassPreConstructorNode::IRClassPreConstructorNode(llvm::Function* irValue, IRInstructionNode* classScopeParameter, std::unordered_map<unsigned long, IRExpressionNode*>* irExpressions, IRBlockNode* irBlock, IRLookupTable* scope) {
    _irValue = irValue;
    _classScopeParameter = classScopeParameter;
    _irExpressions = irExpressions;
    _irBlock = irBlock;
    _scope = scope;
}

llvm::Function* IRClassPreConstructorNode::getFunction() {
    return _irValue;
}

std::unordered_map<unsigned long, IRExpressionNode*>* IRClassPreConstructorNode::getExpressions() {
    return _irExpressions;
}

IRInstructionNode* IRClassPreConstructorNode::getClassScopeParameter() {
    return _classScopeParameter;
}

IRBlockNode* IRClassPreConstructorNode::getBlock() {
    return _irBlock;
}

IRLookupTable* IRClassPreConstructorNode::getScope() {
    return _scope;
}