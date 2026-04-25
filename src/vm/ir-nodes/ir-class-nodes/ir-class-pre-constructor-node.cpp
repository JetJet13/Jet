//
// Created by Johny Georges on 2025-12-27.
//

#include "ir-class-pre-constructor-node.h"

IRClassPreConstructorNode::IRClassPreConstructorNode(llvm::Function* irValue, IRInstructionNode* classScopeParameter, std::vector<std::pair<unsigned long, IRExpressionNode*>>* irExpressions, std::vector<std::pair<unsigned long, llvm::Constant*>>* irInitializers, IRBlockNode* irBlock) {
    _irValue = irValue;
    _classScopeParameter = classScopeParameter;
    _irExpressions = irExpressions;
    _irInitializers = irInitializers;
    _irBlock = irBlock;
}

llvm::Function* IRClassPreConstructorNode::getFunction() {
    return _irValue;
}

std::vector<std::pair<unsigned long, IRExpressionNode*>>* IRClassPreConstructorNode::getExpressions() {
    return _irExpressions;
}

std::vector<std::pair<unsigned long, llvm::Constant*>>* IRClassPreConstructorNode::getInitializers() {
    return _irInitializers;
}

IRInstructionNode* IRClassPreConstructorNode::getClassScopeParameter() {
    return _classScopeParameter;
}

IRBlockNode* IRClassPreConstructorNode::getBlock() {
    return _irBlock;
}