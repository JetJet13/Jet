//
// Created by Johny Georges on 2025-03-19.
//

#include "ir-dref-expression-node.h"
#include "../../../shared/utils/logger/logger.h"

IRDrefExpressionNode::IRDrefExpressionNode(std::shared_ptr<ASTDrefExpressionNode> node, std::shared_ptr<IRExpressionNode> irExpression, std::shared_ptr<IRType> irType, std::shared_ptr<IRInstructionNode> irValue) {
    _node = node;
    _irExpression = irExpression;
    _irType = irType;
    _irValue = irValue;
}

void IRDrefExpressionNode::markAsGlobal() {
    _isGlobal = true;
    _irExpression->markAsGlobal();
}

std::shared_ptr<IRExpressionNode> IRDrefExpressionNode::getExpression() {
    return _irExpression;
}

std::shared_ptr<IRInstructionNode> IRDrefExpressionNode::getIRValue() {
    return _irValue;
}

std::shared_ptr<IRType> IRDrefExpressionNode::getIRType() {
    return _irType;
}

std::shared_ptr<TypeSignature> IRDrefExpressionNode::getTypeSignature() {
    return _node->getTypeSignature();
}

std::shared_ptr<Position> IRDrefExpressionNode::getStartPosition() {
    return _node->getStartPosition();
}

std::shared_ptr<Position> IRDrefExpressionNode::getEndPosition() {
    return _node->getEndPosition();
}

llvm::Value* IRDrefExpressionNode::getValue() {
    return _irValue->getValue();
}

IRNodeType IRDrefExpressionNode::getNodeType() {
    return IR_DREF_EXPRESSION_NODE;
}

std::string IRDrefExpressionNode::toString() {
    return "IR_DREF_EXPRESSION_NODE";
}

void IRDrefExpressionNode::print(std::unique_ptr<llvm::raw_fd_ostream> *stream) {
    _irExpression->print(stream);
}