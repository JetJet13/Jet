//
// Created by Johny Georges on 2026-08-29.
//

#include "ir-class-static-method-access-expression-node.h"
#include "../../../shared/utils/logger/logger.h"

IRClassStaticMethodAccessExpressionNode::IRClassStaticMethodAccessExpressionNode(std::shared_ptr<ASTObjectAccessExpressionNode> node, std::shared_ptr<IRInstructionNode> irStaticMethod, std::shared_ptr<IRType> irType) {
    _node = node;
    _irStaticMethod = irStaticMethod;
    _irType = irType;
}

std::shared_ptr<ASTObjectAccessExpressionNode> IRClassStaticMethodAccessExpressionNode::getNode() {
    return _node;
}

std::shared_ptr<IRPointerType> IRClassStaticMethodAccessExpressionNode::getPointerIRType() {
    return _irStaticMethod->getIRType();
}

std::shared_ptr<IRType> IRClassStaticMethodAccessExpressionNode::getIRType() {
    return _irType;
}

std::shared_ptr<TypeSignature> IRClassStaticMethodAccessExpressionNode::getTypeSignature() {
    return _node->getTypeSignature();
}

std::shared_ptr<Position> IRClassStaticMethodAccessExpressionNode::getStartPosition() {
    return _node->getStartPosition();
}

std::shared_ptr<Position> IRClassStaticMethodAccessExpressionNode::getEndPosition() {
    return _node->getEndPosition();
}

llvm::Value* IRClassStaticMethodAccessExpressionNode::getValue() {
    return _irStaticMethod->getValue();
}

IRNodeType IRClassStaticMethodAccessExpressionNode::getNodeType() {
    return IR_CLASS_STATIC_METHOD_ACCESS_EXPRESSION_NODE;
}

std::string IRClassStaticMethodAccessExpressionNode::toString() {
    return "IR_CLASS_STATIC_METHOD_ACCESS_EXPRESSION_NODE";
}

void IRClassStaticMethodAccessExpressionNode::print(std::unique_ptr<llvm::raw_fd_ostream> *stream) {
    _irStaticMethod->print(stream);
}