//
// Created by Johny Georges on 2024-07-08.
//

#include "ir-function-declaration-node.h"
#include "../../../shared/utils/function-id-generator/function-id-generator.h"

IRFunctionDeclarationNode::IRFunctionDeclarationNode(std::shared_ptr<ASTFunctionDeclarationNode> node, llvm::Function* irValue, IRFunctionParameterListNode* irParameterList, IRBlockNode* irBlock, IRInstructionNode* globalVariable) {
    _node = node;
    _irValue = irValue;
    _irParameterList = irParameterList;
    _irBlock = irBlock;
    _globalVariable = globalVariable;
}

std::string IRFunctionDeclarationNode::getName() {
    return _node->getId();
}

std::string IRFunctionDeclarationNode::getNormalizedName() {
    return _node->getId();
}

IRFunctionParameterListNode* IRFunctionDeclarationNode::getParameters() {
    return _irParameterList;
}

IRInstructionNode* IRFunctionDeclarationNode::getGlobalVariable() {
    return _globalVariable;
}

IRBlockNode* IRFunctionDeclarationNode::getBlock() {
    return _irBlock;
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