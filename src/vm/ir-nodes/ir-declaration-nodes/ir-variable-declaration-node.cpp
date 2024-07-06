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

llvm::GlobalVariable* IRVariableDeclarationNode::asGlobalVariable() {
    if (_irExpression->isConstant()) {
        return new llvm::GlobalVariable(
                _irExpression->getIRValue()->getType(),
                true,
                llvm::GlobalValue::PrivateLinkage,
                _irExpression->getConstantIRValue(),
                _astNode->getId()
        );
    }
    return new llvm::GlobalVariable(
            _irExpression->getIRValue()->getType(),
            true,
            llvm::GlobalValue::PrivateLinkage,
            nullptr,
            _astNode->getId()
    );
}

void IRVariableDeclarationNode::insertSelfIntoBlock(std::unique_ptr<llvm::IRBuilder<>>*  builder) {
    builder->get()->CreateAlloca(_irExpression->getIRValue()->getType(), _irExpression->getIRValue(), _astNode->getId());

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