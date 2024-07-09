//
// Created by Johny Georges on 2024-07-01.
//

#include "ir-variable-declaration-node.h"
#include <llvm/IR/GlobalVariable.h>

IRVariableDeclarationNode::IRVariableDeclarationNode(ASTVariableDeclarationNode* astNode, llvm::AllocaInst* irValue, IRExpressionNode* irExpression) {
    _astNode = astNode;
    _irValue = irValue;
    _irExpression = irExpression;
}

llvm::Value * IRVariableDeclarationNode::insertSelfIntoBlock(std::unique_ptr<llvm::IRBuilder<>>*  builder) {
    builder->get()->Insert(_irValue, _astNode->getId());
    _irExpression->insertSelfIntoBlock(builder, _irValue);
    return _irValue;
}

llvm::AllocaInst* IRVariableDeclarationNode::getIRValue() {
    return _irValue;
}

IRNodeType IRVariableDeclarationNode::getNodeType() {
    return IR_VARIABLE_DECLARATION_NODE;
}

std::string IRVariableDeclarationNode::toString() {
    return "IR_VARIABLE_DECLARATION_NODE";
}

void IRVariableDeclarationNode::print(std::unique_ptr<llvm::raw_fd_ostream> *stream) {
    _irValue->print(**stream);
    stream->get()->write('\n');
    _irExpression->print(stream);
}