//
// Created by Johny Georges on 2026-02-09.
//

#include "ir-function-argument-node.h"

IRFunctionArgumentNode::IRFunctionArgumentNode(IRExpressionNode* irArgument) {
    _irArgument = irArgument;
    _irOperation = new IROperation(IR_FUNCTION_ARGUMENT_OP);
}

IRFunctionArgumentNode::IRFunctionArgumentNode(IRExpressionNode* irArgument, IROperation* irOperation) {
    _irArgument = irArgument;
    _irOperation = irOperation;
}

IRExpressionNode* IRFunctionArgumentNode::getArgument() {
    return _irArgument;
}

IROperation* IRFunctionArgumentNode::getOperation() {
    return _irOperation;
}

IRNodeType IRFunctionArgumentNode::getNodeType() {
    return IR_FUNCTION_ARGUMENT_NODE;
}

std::string IRFunctionArgumentNode::toString() {
    return "IR_FUNCTION_ARGUMENT_NODE";
}

void IRFunctionArgumentNode::print(std::unique_ptr<llvm::raw_fd_ostream> *stream) {
    _irArgument->print(stream);
}