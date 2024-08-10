//
// Created by Johny Georges on 2024-06-29.
//

#include "ir-identifier-expression-node.h"
#include "../../../shared/utils/logger/logger.h"
#include "../../ir-support-functions/ir-copy-array-support-function/ir-copy-array-support-function.h"
#include "../../utils/ir-instruction-node-factory/ir-instruction-node-factory.h"
#include "../../ir-support-functions/ir-array-pointer-support-function/ir-array-pointer-support-function.h"

IRIdentifierExpressionNode::IRIdentifierExpressionNode(ASTIdentifierExpressionNode* node, IRInstructionNode* irValue) {
    _node = node;
    _irValue = irValue;
}

llvm::Value* IRIdentifierExpressionNode::insertSelfIntoBlock(std::unique_ptr<llvm::IRBuilder<>>*  builder) {
    if (_irValue->getIRType()->getSourceType()->isArrayPointerType()) {
        auto destinationAllocation = IRInstructionNodeFactory::create(_irValue->getSourceAllocation()->getSourceAllocation());
        builder->get()->Insert(destinationAllocation->getValue());
        IRCopyArraySupportFunction::insertSelfIntoBlock(
                builder,
                _irValue->getSourceAllocation(),
                destinationAllocation);
        auto arrayPointerType = (IRArrayPointerType*)_irValue->getIRType()->getSourceType();
        auto arrayPointerTypeAllocation = IRInstructionNodeFactory::create(_irValue->getIRType(), destinationAllocation);
        return IRArrayPointerSupportFunction::insertSelfIntoBlock(builder, arrayPointerType, arrayPointerTypeAllocation);
    }
    return builder->get()->CreateLoad(_irValue->getIRType()->getSourceType()->getType(), _irValue->getValue());
}

llvm::Value* IRIdentifierExpressionNode::getValue() {
    return _irValue->getValue();
}

std::optional<IRInstructionNode*> IRIdentifierExpressionNode::getSourceAllocation() {
    return _irValue->getSourceAllocation();
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