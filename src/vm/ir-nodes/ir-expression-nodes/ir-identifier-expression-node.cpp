//
// Created by Johny Georges on 2024-06-29.
//

#include "ir-identifier-expression-node.h"
#include "../../../shared/utils/logger/logger.h"

IRIdentifierExpressionNode::IRIdentifierExpressionNode(std::shared_ptr<ASTIdentifierExpressionNode> node, std::shared_ptr<IRInstructionNode> irValue, std::optional<std::shared_ptr<IRInstructionNode>> irArc) {
    _node = node;
    _irValue = irValue;
    _irArc = irArc;
    _irType = irValue->getIRType();
}

llvm::Value* IRIdentifierExpressionNode::getValue() {
    return _irValue->getValue();
}

std::shared_ptr<IRInstructionNode> IRIdentifierExpressionNode::getIRValue() {
    return _irValue;
}

std::optional<std::shared_ptr<IRInstructionNode>> IRIdentifierExpressionNode::getSourceAllocation() {
    return _irValue;
}

std::optional<std::shared_ptr<IRInstructionNode>> IRIdentifierExpressionNode::getArc() {
    return _irArc;
}

std::shared_ptr<IRType> IRIdentifierExpressionNode::getIRType() {
    return _irType;
}

std::shared_ptr<TypeSignature> IRIdentifierExpressionNode::getTypeSignature() {
    return _node->getTypeSignature();
}

std::shared_ptr<Position> IRIdentifierExpressionNode::getStartPosition() {
    return _node->getStartPosition();
}

std::shared_ptr<Position> IRIdentifierExpressionNode::getEndPosition() {
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