//
// Created by Johny Georges on 2024-12-27.
//

#include "ir-class-method-invocation-expression-node.h"
#include "../../../shared/utils/logger/logger.h"

IRClassMethodInvocationExpressionNode::IRClassMethodInvocationExpressionNode(ASTClassMethodInvocationExpressionNode* node, llvm::Value* irFunction, IRType* irFunctionType, std::vector<IRExpressionNode*> arguments, IRType* type, IRInstructionNode* classScopeArgument) {
    _node = node;
    _irFunction = irFunction;
    _irFunctionType = irFunctionType;
    _arguments = arguments;
    _type = type;
    _classScopeArgument = classScopeArgument;
}

void IRClassMethodInvocationExpressionNode::markAsGlobal() {
    _isGlobal = true;
    for (auto argument : _arguments) {
        argument->markAsGlobal();
    }
}

bool IRClassMethodInvocationExpressionNode::isReferenced() {
    return _node->isReferenced();
}

IRInstructionNode* IRClassMethodInvocationExpressionNode::getClassScopeArgument() {
    return _classScopeArgument;
}

std::vector<IRExpressionNode*>* IRClassMethodInvocationExpressionNode::getIRArguments() {
    return &_arguments;
}

llvm::Value* IRClassMethodInvocationExpressionNode::getValue() {
    return _irFunction;
}

IRType* IRClassMethodInvocationExpressionNode::getFunctionIRType() {
    return _irFunctionType;
}

IRType* IRClassMethodInvocationExpressionNode::getIRType() {
    return _type;
}

TypeSignature* IRClassMethodInvocationExpressionNode::getTypeSignature() {
    return _node->getName()->getTypeSignature()->getReturnType();
}

Position* IRClassMethodInvocationExpressionNode::getStartPosition() {
    return _node->getStartPosition();
}

Position* IRClassMethodInvocationExpressionNode::getEndPosition() {
    return _node->getEndPosition();
}

IRNodeType IRClassMethodInvocationExpressionNode::getNodeType() {
    return IR_CLASS_METHOD_INVOCATION_EXPRESSION_NODE;
}

std::string IRClassMethodInvocationExpressionNode::toString() {
    return "IR_CLASS_METHOD_INVOCATION_EXPRESSION_NODE";
}

void IRClassMethodInvocationExpressionNode::print(std::unique_ptr<llvm::raw_fd_ostream> *stream) {
    _irFunction->print(**stream);
}