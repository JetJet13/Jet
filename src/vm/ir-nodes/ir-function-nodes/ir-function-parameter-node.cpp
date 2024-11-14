//
// Created by Johny Georges on 2024-07-13.
//

#include "ir-function-parameter-node.h"

IRFunctionParameterNode::IRFunctionParameterNode(llvm::Argument* irValue, IRParameterType* parameterType) {
    _irValue = irValue;
    _parameterType = parameterType;
}

llvm::Argument* IRFunctionParameterNode::getArgument() {
    return _irValue;
}

IRParameterType* IRFunctionParameterNode::getParameterType() {
    return _parameterType;
}

IRNodeType IRFunctionParameterNode::getNodeType() {
    return IR_FUNCTION_PARAMETER_NODE;
}

std::string IRFunctionParameterNode::toString() {
    return "IR_FUNCTION_PARAMETER_NODE";
}

void IRFunctionParameterNode::print(std::unique_ptr<llvm::raw_fd_ostream> *stream) {
    _irValue->print(**stream);
}