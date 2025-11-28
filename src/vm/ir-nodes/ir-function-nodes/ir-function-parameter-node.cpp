//
// Created by Johny Georges on 2024-07-13.
//

#include "ir-function-parameter-node.h"

IRFunctionParameterNode::IRFunctionParameterNode(llvm::Argument* irValue, IRParameterType* parameterType, std::optional<ASTFunctionParameterNode*> node) {
    _irValue = irValue;
    _parameterType = parameterType;
    _node = node;
}

llvm::Argument* IRFunctionParameterNode::getArgument() {
    return _irValue;
}

IRParameterType* IRFunctionParameterNode::getParameterType() {
    return _parameterType;
}

bool IRFunctionParameterNode::needsToBeFreed() {
    if (!_node) return false;
    return !_node.value()->isReferenced() &&
           !_node.value()->isCaptured() &&
            _parameterType->getIRType()->containsTypeThatRequiresFreeing();
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