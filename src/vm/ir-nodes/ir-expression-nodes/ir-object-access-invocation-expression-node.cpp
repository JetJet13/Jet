//
// Created by Johny Georges on 2025-06-20.
//

#include "ir-object-access-invocation-expression-node.h"
#include "../../../shared/utils/logger/logger.h"

IRObjectAccessInvocationExpressionNode::IRObjectAccessInvocationExpressionNode(ASTObjectAccessInvocationExpressionNode* node, llvm::Value* irFunction, IRType* irFunctionType, std::vector<IRExpressionNode*> arguments, IRType* type, std::optional<IRExpressionNode*> scopeArgument) {
    _node = node;
    _irFunction = irFunction;
    _irFunctionType = irFunctionType;
    _arguments = arguments;
    _type = type;
    _scopeArgument = scopeArgument;
}

void IRObjectAccessInvocationExpressionNode::markAsGlobal() {
    _isGlobal = true;
    for (auto argument : _arguments) {
        argument->markAsGlobal();
    }
}

llvm::Value* IRObjectAccessInvocationExpressionNode::getFunction() {
    return _irFunction;
}

std::optional<IRExpressionNode*> IRObjectAccessInvocationExpressionNode::getScopeArgument() {
    return _scopeArgument;
}

std::vector<IRExpressionNode*>* IRObjectAccessInvocationExpressionNode::getIRArguments() {
    return &_arguments;
}

llvm::Value* IRObjectAccessInvocationExpressionNode::getValue() {
    return _irFunction;
}

IRType* IRObjectAccessInvocationExpressionNode::getFunctionIRType() {
    return _irFunctionType;
}

IRType* IRObjectAccessInvocationExpressionNode::getIRType() {
    return _type;
}

TypeSignature* IRObjectAccessInvocationExpressionNode::getTypeSignature() {
    return _node->getTypeSignature();
}

IRNodeType IRObjectAccessInvocationExpressionNode::getNodeType() {
    return IR_OBJECT_ACCESS_INVOCATION_EXPRESSION_NODE;
}

std::string IRObjectAccessInvocationExpressionNode::toString() {
    return "IR_OBJECT_ACCESS_INVOCATION_EXPRESSION_NODE";
}

void IRObjectAccessInvocationExpressionNode::print(std::unique_ptr<llvm::raw_fd_ostream> *stream) {
    _irFunction->print(**stream);
}