//
// Created by Johny Georges on 2024-11-08.
//

#include "ir-function-invocation-expression-node.h"
#include "../../../shared/utils/logger/logger.h"

IRFunctionInvocationExpressionNode::IRFunctionInvocationExpressionNode(ASTFunctionInvocationExpressionNode* node, llvm::Value* irFunction, IRType* irFunctionType, std::vector<IRExpressionNode*> arguments, IRType* type, std::optional<IRInstructionNode*> lambdaScopeArgument) {
    _node = node;
    _irFunction = irFunction;
    _irFunctionType = irFunctionType;
    _arguments = arguments;
    _type = type;
    _lambdaScopeArgument = lambdaScopeArgument;
}

void IRFunctionInvocationExpressionNode::markAsGlobal() {
    _isGlobal = true;
    for (auto argument : _arguments) {
        argument->markAsGlobal();
    }
}

std::optional<IRInstructionNode*> IRFunctionInvocationExpressionNode::getLambdaScopeArgument() {
    return _lambdaScopeArgument;
}

std::vector<IRExpressionNode*>* IRFunctionInvocationExpressionNode::getIRArguments() {
    return &_arguments;
}

llvm::Value* IRFunctionInvocationExpressionNode::getValue() {
    return _irFunction;
}

IRType* IRFunctionInvocationExpressionNode::getFunctionIRType() {
    return _irFunctionType;
}

IRType* IRFunctionInvocationExpressionNode::getIRType() {
    return _type;
}

FunctionInvocationTypeSignature* IRFunctionInvocationExpressionNode::getTypeSignature() {
    return _node->getTypeSignature();
}

IRNodeType IRFunctionInvocationExpressionNode::getNodeType() {
    return IR_FUNCTION_INVOCATION_EXPRESSION_NODE;
}

std::string IRFunctionInvocationExpressionNode::toString() {
    return "IR_FUNCTION_INVOCATION_EXPRESSION_NODE";
}

void IRFunctionInvocationExpressionNode::print(std::unique_ptr<llvm::raw_fd_ostream> *stream) {
    _irFunction->print(**stream);
}