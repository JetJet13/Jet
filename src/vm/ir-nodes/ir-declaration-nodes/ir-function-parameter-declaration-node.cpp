//
// Created by Johny Georges on 2024-07-13.
//

#include "ir-function-parameter-declaration-node.h"

IRFunctionParameterDeclarationNode::IRFunctionParameterDeclarationNode(llvm::Argument* argument, IRInstructionNode* irValue) {
    _argument = argument;
    _irValue = irValue;
}

llvm::Argument* IRFunctionParameterDeclarationNode::getArgument() {
    return _argument;
}

IRInstructionNode* IRFunctionParameterDeclarationNode::getAllocation() {
    return _irValue;
}

IRNodeType IRFunctionParameterDeclarationNode::getNodeType() {
    return IR_FUNCTION_PARAMETER_DECLARATION_NODE;
}

std::string IRFunctionParameterDeclarationNode::toString() {
    return "IR_FUNCTION_PARAMETER_DECLARATION_NODE";
}

void IRFunctionParameterDeclarationNode::print(std::unique_ptr<llvm::raw_fd_ostream> *stream) {
    _argument->print(**stream);
}