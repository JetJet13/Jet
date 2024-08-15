//
// Created by Johny Georges on 2024-06-29.
//

#include "ir-identifier-expression-node.h"
#include "../../../shared/utils/logger/logger.h"
#include "../../ir-support-functions/ir-array-pointer-support-function/ir-array-pointer-support-function.h"
#include "../../ir-injector/ir-injector-map.h"

IRIdentifierExpressionNode::IRIdentifierExpressionNode(ASTIdentifierExpressionNode* node, IRInstructionNode* irValue) {
    _node = node;
    _irValue = irValue;
}

llvm::Value* IRIdentifierExpressionNode::insertSelfIntoBlock(std::unique_ptr<llvm::IRBuilder<>> *builder, IRInjectorMap *injectorMap) {
    return injectorMap->getInjector(_node->getTypeSignature())->inject(this, builder);
}

llvm::Value* IRIdentifierExpressionNode::getValue() {
    return _irValue->getValue();
}

std::optional<IRInstructionNode*> IRIdentifierExpressionNode::getSourceAllocation() {
    return _irValue->getSourceAllocation();
}

std::optional<IRInstructionNode*> IRIdentifierExpressionNode::getRootAllocation() {
    return _irValue->getSourceAllocation()->getSourceAllocation();
}

IRPointerType* IRIdentifierExpressionNode::getIRType() {
    return _irValue->getIRType();
}

llvm::Type* IRIdentifierExpressionNode::getTypeAtIndex(unsigned long index) {
    auto type = _irValue->getIRType()->getSourceType()->getType();
    if (type->isArrayTy()) {
        return type->getArrayElementType();
    } else if (type->isStructTy()) {
        return type->getStructElementType(index);
    } else {
        return type;
    }
}

IRNodeType IRIdentifierExpressionNode::getNodeType() {
    return IR_IDENTIFIER_EXPRESSION_NODE;
}

std::string IRIdentifierExpressionNode::toString() {
    return "IR_IDENTIFIER_EXPRESSION_NODE";
}

void IRIdentifierExpressionNode::print(std::unique_ptr<llvm::raw_fd_ostream> *stream) {
    _irValue->print(stream);
}