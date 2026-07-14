//
// Created by Johny Georges on 2026-07-13.
//

#include "ir-share-expression-node.h"

IRShareExpressionNode::IRShareExpressionNode(std::shared_ptr<ASTShareExpressionNode> node, std::shared_ptr<IRExpressionNode> irExpression, std::shared_ptr<IRSharedPtrType> irType, std::shared_ptr<IRInstructionNode> irValue, std::shared_ptr<IRInstructionNode> irArc) {
    _node = node;
    _irExpression = irExpression;
    _irType = irType;
    _irValue = irValue;
    _irArc = irArc;
}

void IRShareExpressionNode::markAsGlobal() {
    _isGlobal = true;
    _irExpression->markAsGlobal();
}

std::shared_ptr<IRExpressionNode> IRShareExpressionNode::getExpression() {
    return _irExpression;
}

std::shared_ptr<IRInstructionNode> IRShareExpressionNode::getIRValue() {
    return _irValue;
}

std::shared_ptr<IRSharedPtrType> IRShareExpressionNode::getIRSharedPtrType() {
    return _irType;
}

std::shared_ptr<IRType> IRShareExpressionNode::getIRType() {
    return _irType;
}

std::shared_ptr<TypeSignature> IRShareExpressionNode::getTypeSignature() {
    return _node->getTypeSignature();
}

std::shared_ptr<Position> IRShareExpressionNode::getStartPosition() {
    return _node->getStartPosition();
}

std::shared_ptr<Position> IRShareExpressionNode::getEndPosition() {
    return _node->getEndPosition();
}

std::optional<std::shared_ptr<IRInstructionNode>> IRShareExpressionNode::getSourceAllocation() {
    return _irValue;
}

std::optional<std::shared_ptr<IRInstructionNode>> IRShareExpressionNode::getArc() {
    return _irArc;
}

llvm::Value* IRShareExpressionNode::getValue() {
    return _irValue->getValue();
}

IRNodeType IRShareExpressionNode::getNodeType() {
    return IR_SHARE_EXPRESSION_NODE;
}

std::string IRShareExpressionNode::toString() {
    return "IR_SHARE_EXPRESSION_NODE";
}

void IRShareExpressionNode::print(std::unique_ptr<llvm::raw_fd_ostream> *stream) {
    _irExpression->print(stream);
}