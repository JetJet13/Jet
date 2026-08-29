//
// Created by Johny Georges on 2026-08-29.
//

#include "ir-class-instance-method-access-expression-node.h"
#include "../../../shared/utils/logger/logger.h"

IRClassInstanceMethodAccessExpressionNode::IRClassInstanceMethodAccessExpressionNode(std::shared_ptr<ASTObjectAccessExpressionNode> node, std::shared_ptr<IRExpressionNode> classInstance, std::shared_ptr<IRInstructionNode> irMethod, std::shared_ptr<IRType> irType) {
    _node = node;
    _classInstance = classInstance;
    _irMethod = irMethod;
    _irType = irType;
}

std::shared_ptr<ASTObjectAccessExpressionNode> IRClassInstanceMethodAccessExpressionNode::getNode() {
    return _node;
}

std::shared_ptr<IRExpressionNode> IRClassInstanceMethodAccessExpressionNode::getClassInstance() {
    return _classInstance;
}

std::shared_ptr<IRInstructionNode> IRClassInstanceMethodAccessExpressionNode::getIRMethod() {
    return _irMethod;
}

std::shared_ptr<IRType> IRClassInstanceMethodAccessExpressionNode::getIRType() {
    return _irType;
}

std::shared_ptr<TypeSignature> IRClassInstanceMethodAccessExpressionNode::getTypeSignature() {
    return _node->getTypeSignature();
}

std::shared_ptr<Position> IRClassInstanceMethodAccessExpressionNode::getStartPosition() {
    return _node->getStartPosition();
}

std::shared_ptr<Position> IRClassInstanceMethodAccessExpressionNode::getEndPosition() {
    return _node->getEndPosition();
}

llvm::Value* IRClassInstanceMethodAccessExpressionNode::getValue() {
    return _irMethod->getValue();
}

IRNodeType IRClassInstanceMethodAccessExpressionNode::getNodeType() {
    return IR_CLASS_INSTANCE_METHOD_ACCESS_EXPRESSION_NODE;
}

std::string IRClassInstanceMethodAccessExpressionNode::toString() {
    return "IR_CLASS_INSTANCE_METHOD_ACCESS_EXPRESSION_NODE";
}

void IRClassInstanceMethodAccessExpressionNode::print(std::unique_ptr<llvm::raw_fd_ostream> *stream) {
    _irMethod->print(stream);
}