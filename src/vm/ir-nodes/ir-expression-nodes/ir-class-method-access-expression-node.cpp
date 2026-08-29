//
// Created by Johny Georges on 2026-08-29.
//

#include "ir-class-method-access-expression-node.h"
#include "../../../shared/utils/logger/logger.h"

IRClassMethodAccessExpressionNode::IRClassMethodAccessExpressionNode(std::shared_ptr<ASTClassPropertyAccessExpressionNode> node, std::shared_ptr<IRInstructionNode> irMethod, std::shared_ptr<IRInvocableType> irType) {
    _node = node;
    _irMethod = irMethod;
    _irType = irType;
}

std::shared_ptr<ASTClassPropertyAccessExpressionNode> IRClassMethodAccessExpressionNode::getNode() {
    return _node;
}

std::shared_ptr<IRInstructionNode> IRClassMethodAccessExpressionNode::getIRMethod() {
    return _irMethod;
}

std::shared_ptr<IRType> IRClassMethodAccessExpressionNode::getIRType() {
    return _irType;
}

std::shared_ptr<TypeSignature> IRClassMethodAccessExpressionNode::getTypeSignature() {
    return _node->getTypeSignature();
}

std::shared_ptr<Position> IRClassMethodAccessExpressionNode::getStartPosition() {
    return _node->getStartPosition();
}

std::shared_ptr<Position> IRClassMethodAccessExpressionNode::getEndPosition() {
    return _node->getEndPosition();
}

llvm::Value* IRClassMethodAccessExpressionNode::getValue() {
    return _irMethod->getValue();
}

IRNodeType IRClassMethodAccessExpressionNode::getNodeType() {
    return IR_CLASS_METHOD_ACCESS_EXPRESSION_NODE;
}

std::string IRClassMethodAccessExpressionNode::toString() {
    return "IR_CLASS_METHOD_ACCESS_EXPRESSION_NODE";
}

void IRClassMethodAccessExpressionNode::print(std::unique_ptr<llvm::raw_fd_ostream> *stream) {
    _irMethod->print(stream);
}