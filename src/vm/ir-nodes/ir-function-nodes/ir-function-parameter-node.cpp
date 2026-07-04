//
// Created by Johny Georges on 2024-07-13.
//

#include "ir-function-parameter-node.h"

IRFunctionParameterNode::IRFunctionParameterNode(llvm::Argument* irValue, IRParameterType* parameterType, IRInstructionNode* allocation, std::optional<std::shared_ptr<ASTFunctionParameterNode>> node, std::optional<IRInstructionNode*> irArc) {
    _irValue = irValue;
    _parameterType = parameterType;
    _allocation = allocation;
    _node = node;
    _irArc = irArc;
}

llvm::Argument* IRFunctionParameterNode::getArgument() {
    return _irValue;
}

IRParameterType* IRFunctionParameterNode::getParameterType() {
    return _parameterType;
}

IRInstructionNode* IRFunctionParameterNode::getAllocation() {
    return _allocation;
}

std::optional<IRInstructionNode*> IRFunctionParameterNode::getArc() {
    return _irArc;
}

bool IRFunctionParameterNode::isCaptured() {
    if (!_node) return false;
    return _node.value()->isCaptured();
}

unsigned long IRFunctionParameterNode::getCaptureCount() {
    if (!_node) return 0;
    return _node.value()->getCaptureCount();
}

bool IRFunctionParameterNode::needsToBeFreed() {
    if (!_node) return false;
    return !_node.value()->isCaptured() &&
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