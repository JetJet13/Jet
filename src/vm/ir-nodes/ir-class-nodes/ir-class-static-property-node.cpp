//
// Created by Johny Georges on 2026-03-14.
//

#include "ir-class-static-property-node.h"

IRClassStaticPropertyNode::IRClassStaticPropertyNode(std::shared_ptr<ASTClassPropertyDeclarationNode> node, llvm::GlobalVariable* irValue, IRExpressionNode* initialIRValue, IRType* irType) {
    _node = node;
    _irValue = irValue;
    _initialIRValue = initialIRValue;
    _irType = irType;
}

llvm::GlobalVariable* IRClassStaticPropertyNode::getGlobalVariable() {
    return _irValue;
}

IRExpressionNode* IRClassStaticPropertyNode::getInitialIRValue() {
    return _initialIRValue;
}

IRType* IRClassStaticPropertyNode::getIRType() {
    return _irType;
}