//
// Created by Johny Georges on 2024-07-08.
//

#include "ir-function-declaration-node.h"

IRFunctionDeclarationNode::IRFunctionDeclarationNode(ASTFunctionDeclarationNode* node, llvm::Function* irValue, IRFunctionParameterListNode* irParameterList, IRBlockNode* irBlock) {
    _node = node;
    _irValue = irValue;
    _irParameterList = irParameterList;
    _irBlock = irBlock;
}

llvm::Value* IRFunctionDeclarationNode::getValue() {
    return _irValue;
}

IRNodeType IRFunctionDeclarationNode::getNodeType() {
    return IR_FUNCTION_DECLARATION_NODE;
}

std::string IRFunctionDeclarationNode::toString() {
    return "IR_FUNCTION_DECLARATION_NODE";
}

void IRFunctionDeclarationNode::print(std::unique_ptr<llvm::raw_fd_ostream> *stream) {
    _irValue->print(**stream);
}