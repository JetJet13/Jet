//
// Created by Johny Georges on 2024-12-30.
//

#include "ir-new-class-instance-expression-node.h"
#include "../../../shared/utils/logger/logger.h"

IRNewClassInstanceExpressionNode::IRNewClassInstanceExpressionNode(std::shared_ptr<ASTNewClassInstanceExpressionNode> node, std::string constructorId, std::shared_ptr<IRFunctionType> irConstructorType, std::vector<std::shared_ptr<IRFunctionArgumentNode>> arguments, std::shared_ptr<IRNewClassInstanceType> type, std::shared_ptr<IRInstructionNode> classInstanceAllocation, std::shared_ptr<IRInstructionNode> irArc) {
    _node = node;
    _constructorId = constructorId;
    _irConstructorType = irConstructorType;
    _arguments = arguments;
    _type = type;
    _classInstanceAllocation = classInstanceAllocation;
    _irArc = irArc;
}

void IRNewClassInstanceExpressionNode::markAsGlobal() {
    _isGlobal = true;
    for (auto argument : _arguments) {
        argument->getArgument()->markAsGlobal();
    }
}

std::shared_ptr<IRInstructionNode> IRNewClassInstanceExpressionNode::getClassInstanceAllocation() {
    return _classInstanceAllocation;
}

std::vector<std::shared_ptr<IRFunctionArgumentNode>>* IRNewClassInstanceExpressionNode::getIRArguments() {
    return &_arguments;
}

std::optional<std::shared_ptr<IRInstructionNode>> IRNewClassInstanceExpressionNode::getArc() {
    return _irArc;
}

llvm::Value* IRNewClassInstanceExpressionNode::getValue() {
    return _classInstanceAllocation->getValue();
}

std::shared_ptr<IRFunctionType> IRNewClassInstanceExpressionNode::getConstructorIRType() {
    return _irConstructorType;
}

std::string IRNewClassInstanceExpressionNode::getConstructorId() {
    return _constructorId;
}

std::shared_ptr<IRNewClassInstanceType> IRNewClassInstanceExpressionNode::getIRClassInstanceType() {
    return _type;
}

std::shared_ptr<IRType> IRNewClassInstanceExpressionNode::getIRType() {
    return _type;
}

std::shared_ptr<TypeSignature> IRNewClassInstanceExpressionNode::getTypeSignature() {
    return _node->getTypeSignature();
}

std::shared_ptr<Position> IRNewClassInstanceExpressionNode::getStartPosition() {
    return _node->getStartPosition();
}

std::shared_ptr<Position> IRNewClassInstanceExpressionNode::getEndPosition() {
    return _node->getEndPosition();
}

IRNodeType IRNewClassInstanceExpressionNode::getNodeType() {
    return IR_NEW_CLASS_INSTANCE_EXPRESSION_NODE;
}

std::string IRNewClassInstanceExpressionNode::toString() {
    return "IR_NEW_CLASS_INSTANCE_EXPRESSION_NODE";
}

void IRNewClassInstanceExpressionNode::print(std::unique_ptr<llvm::raw_fd_ostream> *stream) {
    Logger::log(this->toString(), _constructorId);
}