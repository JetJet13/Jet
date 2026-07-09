//
// Created by Johny Georges on 2025-02-10.
//

#include "ir-ref-expression-node.h"

IRRefExpressionNode::IRRefExpressionNode(std::shared_ptr<ASTRefExpressionNode> node, std::shared_ptr<IRExpressionNode> irExpression, std::shared_ptr<IRRefType> irType, std::shared_ptr<IRInstructionNode> irValue, std::shared_ptr<IRInstructionNode> irArc) {
    _node = node;
    _irExpression = irExpression;
    _irType = irType;
    _irValue = irValue;
    _irArc = irArc;
}

void IRRefExpressionNode::markAsGlobal() {
    _isGlobal = true;
    _irExpression->markAsGlobal();
}

std::shared_ptr<IRExpressionNode> IRRefExpressionNode::getExpression() {
    return _irExpression;
}

std::shared_ptr<IRInstructionNode> IRRefExpressionNode::getIRValue() {
    return _irValue;
}

std::shared_ptr<IRRefType> IRRefExpressionNode::getIRRefType() {
    return _irType;
}

std::shared_ptr<IRType> IRRefExpressionNode::getIRType() {
    return _irType;
}

std::shared_ptr<TypeSignature> IRRefExpressionNode::getTypeSignature() {
    return _node->getTypeSignature();
}

std::shared_ptr<Position> IRRefExpressionNode::getStartPosition() {
    return _node->getStartPosition();
}

std::shared_ptr<Position> IRRefExpressionNode::getEndPosition() {
    return _node->getEndPosition();
}

std::optional<std::shared_ptr<IRInstructionNode>> IRRefExpressionNode::getSourceAllocation() {
    return _irValue;
}

std::optional<std::shared_ptr<IRInstructionNode>> IRRefExpressionNode::getArc() {
    return _irArc;
}

llvm::Value* IRRefExpressionNode::getValue() {
    return _irValue->getValue();
}

IRNodeType IRRefExpressionNode::getNodeType() {
    return IR_REF_EXPRESSION_NODE;
}

std::string IRRefExpressionNode::toString() {
    return "IR_REF_EXPRESSION_NODE";
}

void IRRefExpressionNode::print(std::unique_ptr<llvm::raw_fd_ostream> *stream) {
    _irExpression->print(stream);
}