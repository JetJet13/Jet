//
// Created by Johny Georges on 2024-11-28.
//

#include "ir-function-parameter-invocation-expression-node.h"

IRFunctionParameterInvocationExpressionNode::IRFunctionParameterInvocationExpressionNode(ASTFunctionInvocationExpressionNode* node, llvm::Value* irFunction, llvm::Value* irFunctionScopeArgument, IRFunctionParameterType* irFunctionType, std::vector<IRExpressionNode*> arguments, IRType* type) {
    _node = node;
    _irFunction = irFunction;
    _irFunctionScopeArgument = irFunctionScopeArgument;
    _irFunctionType = irFunctionType;
    _arguments = arguments;
    _type = type;
}

std::vector<IRExpressionNode*>* IRFunctionParameterInvocationExpressionNode::getIRArguments() {
    return &_arguments;
}

llvm::Value* IRFunctionParameterInvocationExpressionNode::getValue() {
    return _irFunction;
}

llvm::Value* IRFunctionParameterInvocationExpressionNode::getFunction() {
    return _irFunction;
}

llvm::Value* IRFunctionParameterInvocationExpressionNode::getFunctionScopeArgument() {
    return _irFunctionScopeArgument;
}

IRFunctionParameterType* IRFunctionParameterInvocationExpressionNode::getFunctionIRType() {
    return _irFunctionType;
}

IRType* IRFunctionParameterInvocationExpressionNode::getIRType() {
    return _type;
}

FunctionInvocationTypeSignature* IRFunctionParameterInvocationExpressionNode::getTypeSignature() {
    return _node->getTypeSignature();
}

IRNodeType IRFunctionParameterInvocationExpressionNode::getNodeType() {
    return IR_FUNCTION_PARAMETER_INVOCATION_EXPRESSION_NODE;
}

std::string IRFunctionParameterInvocationExpressionNode::toString() {
    return "IR_FUNCTION_PARAMETER_INVOCATION_EXPRESSION_NODE";
}

void IRFunctionParameterInvocationExpressionNode::print(std::unique_ptr<llvm::raw_fd_ostream> *stream) {
    _irFunction->print(**stream);
    _irFunctionScopeArgument->print(**stream);
}