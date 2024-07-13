//
// Created by Johny Georges on 2024-07-08.
//

#include "ir-function-parameter-list-node.h"

IRFunctionParameterListNode::IRFunctionParameterListNode(ASTFunctionParameterListNode* node, std::vector<IRFunctionParameterNode*> parameters) {
    _node = node;
    _parameters = parameters;
}

std::vector<IRFunctionParameterNode*>* IRFunctionParameterListNode::getParameters() {
    return &_parameters;
}

std::vector<llvm::Argument*> IRFunctionParameterListNode::getArguments() {
    auto arguments = std::vector<llvm::Argument*>();
    for (auto parameter : _parameters) {
        arguments.push_back(parameter->getArgument());
    }
    return arguments;
}

IRNodeType IRFunctionParameterListNode::getNodeType() {
    return IR_FUNCTION_PARAMETER_LIST_NODE;
}

std::string IRFunctionParameterListNode::toString() {
    return "IR_FUNCTION_PARAMETER_LIST_NODE";
}

void IRFunctionParameterListNode::print(std::unique_ptr<llvm::raw_fd_ostream> *stream) {
    for (auto parameter : _parameters) {
        parameter->print(stream);
    }
}