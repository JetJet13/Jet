//
// Created by Johny Georges on 2024-11-08.
//

#include "ir-function-invocation-expression-node.h"
#include "../../../shared/utils/logger/logger.h"

IRFunctionInvocationExpressionNode::IRFunctionInvocationExpressionNode(ASTFunctionInvocationExpressionNode* node, llvm::CallInst* irFunctionCall, IRType* type) {
    _node = node;
    _irFunctionCall = irFunctionCall;
    _type = type;
}

llvm::Value* IRFunctionInvocationExpressionNode::getValue() {
    return _irFunctionCall;
}

IRType* IRFunctionInvocationExpressionNode::getIRType() {
    return _type;
}

TypeSignature* IRFunctionInvocationExpressionNode::getTypeSignature() {
    return _node->getTypeSignature();
}

IRNodeType IRFunctionInvocationExpressionNode::getNodeType() {
    return IR_FUNCTION_INVOCATION_EXPRESSION_NODE;
}

std::string IRFunctionInvocationExpressionNode::toString() {
    return "IR_FUNCTION_INVOCATION_EXPRESSION_NODE";
}

void IRFunctionInvocationExpressionNode::print(std::unique_ptr<llvm::raw_fd_ostream> *stream) {
    _irFunctionCall->print(**stream);
}