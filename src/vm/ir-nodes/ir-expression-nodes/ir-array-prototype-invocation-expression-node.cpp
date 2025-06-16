//
// Created by Johny Georges on 2025-06-16.
//

#include "ir-array-prototype-invocation-expression-node.h"
#include "../../../shared/utils/logger/logger.h"

IRArrayPrototypeInvocationExpressionNode::IRArrayPrototypeInvocationExpressionNode(ASTObjectAccessInvocationExpressionNode* node, llvm::Value* irFunction, IRType* irFunctionType, std::vector<IRExpressionNode*> arguments, IRType* type, IRExpressionNode* irArray) {
    _node = node;
    _irFunction = irFunction;
    _irFunctionType = irFunctionType;
    _arguments = arguments;
    _type = type;
    _irArray = irArray;
}

void IRArrayPrototypeInvocationExpressionNode::markAsGlobal() {
    _isGlobal = true;
    for (auto argument : _arguments) {
        argument->markAsGlobal();
    }
}

IRExpressionNode* IRArrayPrototypeInvocationExpressionNode::getIRArrayValue() {
    return _irArray;
}

std::vector<IRExpressionNode*>* IRArrayPrototypeInvocationExpressionNode::getIRArguments() {
    return &_arguments;
}

llvm::Value* IRArrayPrototypeInvocationExpressionNode::getValue() {
    return _irFunction;
}

IRType* IRArrayPrototypeInvocationExpressionNode::getFunctionIRType() {
    return _irFunctionType;
}

IRType* IRArrayPrototypeInvocationExpressionNode::getIRType() {
    return _type;
}

TypeSignature* IRArrayPrototypeInvocationExpressionNode::getTypeSignature() {
    return _node->getTypeSignature();
}

IRNodeType IRArrayPrototypeInvocationExpressionNode::getNodeType() {
    return IR_ARRAY_PROTOTYPE_INVOCATION_EXPRESSION_NODE;
}

std::string IRArrayPrototypeInvocationExpressionNode::toString() {
    return "IR_ARRAY_PROTOTYPE_INVOCATION_EXPRESSION_NODE";
}

void IRArrayPrototypeInvocationExpressionNode::print(std::unique_ptr<llvm::raw_fd_ostream> *stream) {
    _irFunction->print(**stream);
}