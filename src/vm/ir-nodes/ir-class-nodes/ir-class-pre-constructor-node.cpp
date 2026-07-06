//
// Created by Johny Georges on 2025-12-27.
//

#include "ir-class-pre-constructor-node.h"

IRClassPreConstructorNode::IRClassPreConstructorNode(llvm::Function* irValue, std::shared_ptr<IRInstructionNode> classScopeParameter, std::vector<std::pair<unsigned long, std::shared_ptr<IRExpressionNode>>>* irExpressions, std::vector<std::pair<unsigned long, llvm::Constant*>>* irInitializers, std::shared_ptr<IRBlockNode> irBlock) {
    _irValue = irValue;
    _classScopeParameter = classScopeParameter;
    _irExpressions = irExpressions;
    _irInitializers = irInitializers;
    _irBlock = irBlock;
}

llvm::Function* IRClassPreConstructorNode::getFunction() {
    return _irValue;
}

std::vector<std::pair<unsigned long, std::shared_ptr<IRExpressionNode>>>* IRClassPreConstructorNode::getExpressions() {
    return _irExpressions;
}

std::vector<std::pair<unsigned long, llvm::Constant*>>* IRClassPreConstructorNode::getInitializers() {
    return _irInitializers;
}

std::shared_ptr<IRInstructionNode> IRClassPreConstructorNode::getClassScopeParameter() {
    return _classScopeParameter;
}

std::shared_ptr<IRBlockNode> IRClassPreConstructorNode::getBlock() {
    return _irBlock;
}