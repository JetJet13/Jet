//
// Created by Johny Georges on 2024-11-08.
//

#include "ir-function-invocation-expression-node.h"
#include "../../../shared/utils/logger/logger.h"

IRFunctionInvocationExpressionNode::IRFunctionInvocationExpressionNode(ASTFunctionInvocationExpressionNode* node, llvm::Function* irFunction, std::vector<IRExpressionNode*> arguments, IRType* type, std::optional<IRInstructionNode*> lambdaScopeArgument) {
    _node = node;
    _irFunction = irFunction;
    _arguments = arguments;
    _type = type;
    _lambdaScopeArgument = lambdaScopeArgument;
}

std::optional<IRInstructionNode*> IRFunctionInvocationExpressionNode::getLambdaScopeArgument() {
    return _lambdaScopeArgument;
}

std::vector<IRExpressionNode*>* IRFunctionInvocationExpressionNode::getIRArguments() {
    return &_arguments;
}

llvm::Function* IRFunctionInvocationExpressionNode::getValue() {
    return _irFunction;
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