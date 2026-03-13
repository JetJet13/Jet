//
// Created by Johny Georges on 2024-06-29.
//

#include "ir-identifier-expression-node.h"
#include "../../../shared/utils/logger/logger.h"

IRIdentifierExpressionNode::IRIdentifierExpressionNode(ASTIdentifierExpressionNode* node, IRInstructionNode* irValue, std::optional<IRInstructionNode*> irArc) {
    _node = node;
    _irValue = irValue;
    _irArc = irArc;
    _irType = irValue->getIRType()->clone();
}

llvm::Value* IRIdentifierExpressionNode::getValue() {
    return _irValue->getValue();
}

IRInstructionNode* IRIdentifierExpressionNode::getIRValue() {
    return _irValue;
}

std::optional<IRInstructionNode*> IRIdentifierExpressionNode::getSourceAllocation() {
    return _irValue;
}

std::optional<IRInstructionNode*> IRIdentifierExpressionNode::getArc() {
    return _irArc;
}

IRPointerType* IRIdentifierExpressionNode::getIRType() {
    return _irType;
}

TypeSignature* IRIdentifierExpressionNode::getTypeSignature() {
    return _node->getTypeSignature();
}

Position* IRIdentifierExpressionNode::getStartPosition() {
    return _node->getStartPosition();
}

Position* IRIdentifierExpressionNode::getEndPosition() {
    return _node->getEndPosition();
}

llvm::Type* IRIdentifierExpressionNode::getTypeAtIndex(unsigned long index) {
    auto type = _irValue->getIRType()->getUnderlyingType()->getType();
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