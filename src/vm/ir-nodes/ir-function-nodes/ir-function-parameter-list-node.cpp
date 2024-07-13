//
// Created by Johny Georges on 2024-07-08.
//

#include "ir-function-parameter-list-node.h"

IRFunctionParameterListNode::IRFunctionParameterListNode(ASTFunctionParameterListNode* node, std::vector<llvm::Argument*> irValues) {
    _node = node;
    _irValues = irValues;
}

std::vector<llvm::Argument*>* IRFunctionParameterListNode::getArguments() {
    return &_irValues;
}

IRNodeType IRFunctionParameterListNode::getNodeType() {
    return IR_FUNCTION_PARAMETER_LIST_NODE;
}

std::string IRFunctionParameterListNode::toString() {
    return "IR_FUNCTION_PARAMETER_LIST_NODE";
}

void IRFunctionParameterListNode::print(std::unique_ptr<llvm::raw_fd_ostream> *stream) {
    for (auto value : _irValues) {
        value->print(**stream);
    }
}