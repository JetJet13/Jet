//
// Created by Johny Georges on 2025-02-10.
//

#include "ir-ref-expression-node.h"

IRRefExpressionNode::IRRefExpressionNode(ASTRefExpressionNode* node, IRExpressionNode* irExpression, IRRefType* irType, IRInstructionNode* irValue, IRInstructionNode* irArc) {
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

IRExpressionNode* IRRefExpressionNode::getExpression() {
    return _irExpression;
}

IRInstructionNode* IRRefExpressionNode::getIRValue() {
    return _irValue;
}

IRRefType* IRRefExpressionNode::getIRType() {
    return _irType;
}

TypeSignature* IRRefExpressionNode::getTypeSignature() {
    return _node->getTypeSignature();
}

Position* IRRefExpressionNode::getStartPosition() {
    return _node->getStartPosition();
}

Position* IRRefExpressionNode::getEndPosition() {
    return _node->getEndPosition();
}

std::optional<IRInstructionNode*> IRRefExpressionNode::getSourceAllocation() {
    return _irValue;
}

std::optional<IRInstructionNode*> IRRefExpressionNode::getArc() {
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