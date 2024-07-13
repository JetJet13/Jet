//
// Created by Johny Georges on 2024-07-13.
//

#include "ir-function-parameter-declaration-node.h"

IRFunctionParameterDeclarationNode::IRFunctionParameterDeclarationNode(llvm::Argument* argument, llvm::AllocaInst* irValue) {
    _argument = argument;
    _irValue = irValue;
}

void IRFunctionParameterDeclarationNode::insertSelfIntoBlock(std::unique_ptr<llvm::IRBuilder<>>*  builder) {
    builder->get()->Insert(_irValue);
    builder->get()->CreateStore(_argument, _irValue);
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