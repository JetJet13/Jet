//
// Created by Johny Georges on 2024-06-29.
//

#include "ir-identifier-expression-node.h"
#include "../../../shared/utils/logger/logger.h"

IRIdentifierExpressionNode::IRIdentifierExpressionNode(ASTIdentifierExpressionNode* node, IRInstructionNode* irValue) {
    _node = node;
    _irValue = irValue;
}

llvm::Value* IRIdentifierExpressionNode::insertSelfIntoBlock(std::unique_ptr<llvm::IRBuilder<>>*  builder) {
    auto type = _irValue->getIRType()->getPointerSourceIRType()->getType();
    auto allocation = builder->get()->CreateAlloca(type);
    auto loadedValue = builder->get()->CreateLoad(type, _irValue->getSourceAllocation()->getValue());
    builder->get()->CreateStore(loadedValue, allocation);
    return allocation;
}

llvm::Value* IRIdentifierExpressionNode::getValue() {
    return _irValue->getValue();
}

IRInstructionNode* IRIdentifierExpressionNode::getSourceAllocation() {
    return _irValue->getSourceAllocation();
}

IRPointerType* IRIdentifierExpressionNode::getIRType() {
    return _irValue->getIRType();
}

llvm::Type* IRIdentifierExpressionNode::getTypeAtIndex(unsigned long index) {
    auto type = _irValue->getIRType()->getPointerSourceIRType()->getType();
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