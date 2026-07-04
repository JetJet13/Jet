//
// Created by Johny Georges on 2026-03-16.
//

#include "ir-class-static-method-invocation-expression-node.h"
#include "../../../shared/utils/logger/logger.h"

IRClassStaticMethodInvocationExpressionNode::IRClassStaticMethodInvocationExpressionNode(std::shared_ptr<ASTObjectAccessInvocationExpressionNode> node, IRInstructionNode* irFunction, llvm::CallInst* irCallInstruction, IRType* irFunctionType, std::vector<IRFunctionArgumentNode*> arguments, IRType* type) {
    _node = node;
    _irCallInstruction = irCallInstruction;
    _irFunction = irFunction;
    _irFunctionType = irFunctionType;
    _arguments = arguments;
    _type = type;
}

void IRClassStaticMethodInvocationExpressionNode::markAsGlobal() {
    _isGlobal = true;
    for (auto argument : _arguments) {
        argument->getArgument()->markAsGlobal();
    }
}

IRInstructionNode* IRClassStaticMethodInvocationExpressionNode::getFunction() {
    return _irFunction;
}

std::vector<IRFunctionArgumentNode*>* IRClassStaticMethodInvocationExpressionNode::getIRArguments() {
    return &_arguments;
}

llvm::CallInst* IRClassStaticMethodInvocationExpressionNode::getValue() {
    return _irCallInstruction;
}

llvm::Value* IRClassStaticMethodInvocationExpressionNode::getFunctionValue() {
    return _irFunction->getValue();
}

IRType* IRClassStaticMethodInvocationExpressionNode::getFunctionIRType() {
    return _irFunctionType;
}

IRType* IRClassStaticMethodInvocationExpressionNode::getIRType() {
    return _type;
}

std::shared_ptr<TypeSignature> IRClassStaticMethodInvocationExpressionNode::getTypeSignature() {
    return _node->getTypeSignature();
}

Position* IRClassStaticMethodInvocationExpressionNode::getStartPosition() {
    return _node->getStartPosition();
}

Position* IRClassStaticMethodInvocationExpressionNode::getEndPosition() {
    return _node->getEndPosition();
}

IRNodeType IRClassStaticMethodInvocationExpressionNode::getNodeType() {
    return IR_CLASS_STATIC_METHOD_INVOCATION_EXPRESSION_NODE;
}

std::string IRClassStaticMethodInvocationExpressionNode::toString() {
    return "IR_CLASS_STATIC_METHOD_INVOCATION_EXPRESSION_NODE";
}

void IRClassStaticMethodInvocationExpressionNode::print(std::unique_ptr<llvm::raw_fd_ostream> *stream) {
    _irFunction->getValue()->print(**stream);
}