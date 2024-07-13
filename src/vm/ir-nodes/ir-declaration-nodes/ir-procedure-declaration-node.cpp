//
// Created by Johny Georges on 2024-07-13.
//

#include "ir-procedure-declaration-node.h"

IRProcedureDeclarationNode::IRProcedureDeclarationNode(ASTProcedureDeclarationNode* node, llvm::Function* irValue, IRFunctionParameterListNode* irParameterList, IRBlockNode* irBlock) {
    _node = node;
    _irValue = irValue;
    _irParameterList = irParameterList;
    _irBlock = irBlock;
}

void IRProcedureDeclarationNode::insertSelfIntoBlock(std::unique_ptr<llvm::IRBuilder<>>*  builder) {

}

IRNodeType IRProcedureDeclarationNode::getNodeType() {
    return IR_PROCEDURE_DECLARATION_NODE;
}

std::string IRProcedureDeclarationNode::toString() {
    return "IR_PROCEDURE_DECLARATION_NODE";
}

void IRProcedureDeclarationNode::print(std::unique_ptr<llvm::raw_fd_ostream> *stream) {
    _irValue->print(**stream);
}