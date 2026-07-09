//
// Created by Johny Georges on 2026-03-21.
//

#include "ir-string-prototype-invocation-expression-node.h"
#include "../../../shared/utils/logger/logger.h"

IRStringPrototypeInvocationExpressionNode::IRStringPrototypeInvocationExpressionNode(std::shared_ptr<ASTObjectAccessInvocationExpressionNode> node, llvm::Value* irFunction, llvm::CallInst* irCallInstruction, std::shared_ptr<IRType> irFunctionType, std::vector<std::shared_ptr<IRFunctionArgumentNode>> arguments, std::shared_ptr<IRType> type, std::shared_ptr<IRExpressionNode> irString) {
    _node = node;
    _irCallInstruction = irCallInstruction;
    _irFunction = irFunction;
    _irFunctionType = irFunctionType;
    _arguments = arguments;
    _type = type;
    _irString = irString;
}

void IRStringPrototypeInvocationExpressionNode::markAsGlobal() {
    _isGlobal = true;
    for (auto argument : _arguments) {
        argument->getArgument()->markAsGlobal();
    }
}

std::shared_ptr<IRExpressionNode> IRStringPrototypeInvocationExpressionNode::getIRStringValue() {
    return _irString;
}

std::vector<std::shared_ptr<IRFunctionArgumentNode>>* IRStringPrototypeInvocationExpressionNode::getIRArguments() {
    return &_arguments;
}

llvm::CallInst* IRStringPrototypeInvocationExpressionNode::getValue() {
    return _irCallInstruction;
}


llvm::Value* IRStringPrototypeInvocationExpressionNode::getFunctionValue() {
    return _irFunction;
}

std::shared_ptr<IRType> IRStringPrototypeInvocationExpressionNode::getFunctionIRType() {
    return _irFunctionType;
}

std::shared_ptr<IRType> IRStringPrototypeInvocationExpressionNode::getIRType() {
    return _type;
}

std::shared_ptr<TypeSignature> IRStringPrototypeInvocationExpressionNode::getTypeSignature() {
    return _node->getTypeSignature();
}

std::shared_ptr<Position> IRStringPrototypeInvocationExpressionNode::getStartPosition() {
    return _node->getStartPosition();
}

std::shared_ptr<Position> IRStringPrototypeInvocationExpressionNode::getEndPosition() {
    return _node->getEndPosition();
}

IRNodeType IRStringPrototypeInvocationExpressionNode::getNodeType() {
    return IR_STRING_PROTOTYPE_INVOCATION_EXPRESSION_NODE;
}

std::string IRStringPrototypeInvocationExpressionNode::toString() {
    return "IR_STRING_PROTOTYPE_INVOCATION_EXPRESSION_NODE";
}

void IRStringPrototypeInvocationExpressionNode::print(std::unique_ptr<llvm::raw_fd_ostream> *stream) {
    _irFunction->print(**stream);
}