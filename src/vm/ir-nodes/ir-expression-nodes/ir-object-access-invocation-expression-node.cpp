//
// Created by Johny Georges on 2025-06-20.
//

#include "ir-object-access-invocation-expression-node.h"
#include "../../../shared/utils/logger/logger.h"

IRObjectAccessInvocationExpressionNode::IRObjectAccessInvocationExpressionNode(ASTObjectAccessInvocationExpressionNode* node, IRObjectAccessExpressionNode* irObjectAccessExpression, IRType* irFunctionType, std::vector<IRExpressionNode*> arguments, IRType* type) {
    _node = node;
    _irObjectAccessExpression = irObjectAccessExpression;
    _irFunctionType = irFunctionType;
    _arguments = arguments;
    _type = type;
}

void IRObjectAccessInvocationExpressionNode::markAsGlobal() {
    _isGlobal = true;
    for (auto argument : _arguments) {
        argument->markAsGlobal();
    }
}

IRObjectAccessExpressionNode* IRObjectAccessInvocationExpressionNode::getIRObjectAccessExpression() {
    return _irObjectAccessExpression;
}

std::vector<IRExpressionNode*>* IRObjectAccessInvocationExpressionNode::getIRArguments() {
    return &_arguments;
}

llvm::Value* IRObjectAccessInvocationExpressionNode::getValue() {
    return _irObjectAccessExpression->getValue();
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
    _irObjectAccessExpression->getValue()->print(**stream);
}