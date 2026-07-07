//
// Created by Johny Georges on 2026-02-09.
//

#include "ir-function-argument-node.h"

IRFunctionArgumentNode::IRFunctionArgumentNode(std::shared_ptr<IRExpressionNode> irArgument) {
    _irArgument = irArgument;
    _irOperation = std::make_shared<IROperation>(IR_FUNCTION_ARGUMENT_OP);
}

IRFunctionArgumentNode::IRFunctionArgumentNode(std::shared_ptr<IRExpressionNode> irArgument, std::shared_ptr<IROperation> irOperation) {
    _irArgument = irArgument;
    _irOperation = irOperation;
}

std::shared_ptr<IRExpressionNode> IRFunctionArgumentNode::getArgument() {
    return _irArgument;
}

std::shared_ptr<IROperation> IRFunctionArgumentNode::getOperation() {
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