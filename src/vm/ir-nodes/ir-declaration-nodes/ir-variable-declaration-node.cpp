//
// Created by Johny Georges on 2024-07-01.
//

#include "ir-variable-declaration-node.h"

IRVariableDeclarationNode::IRVariableDeclarationNode(ASTVariableDeclarationNode* astNode, IRInstructionNode* irValue, IRExpressionNode* irExpression) {
    _astNode = astNode;
    _irValue = irValue;
    _irExpression = irExpression;
}

void IRVariableDeclarationNode::insertSelfIntoBlock(std::unique_ptr<llvm::IRBuilder<>>*  builder) {
    builder->get()->Insert(_irValue->getValue(), _astNode->getId());
    auto irExpressionValue = _irExpression->insertSelfIntoBlock(builder);
    if (_irExpression->is(IR_OBJECT_ACCESS_EXPRESSION_NODE)) {
        auto pointer = builder->get()->Insert(irExpressionValue);
        auto loadedValue = builder->get()->CreateLoad(_irValue->getIRType()->getType(), pointer);
        builder->get()->CreateStore(loadedValue, _irValue->getValue());
    } else if (_irExpression->is(IR_IDENTIFIER_EXPRESSION_NODE)) {
        auto loadedValue = builder->get()->CreateLoad(_irValue->getIRType()->getType(), irExpressionValue);
        builder->get()->CreateStore(loadedValue, _irValue->getValue());
    } else {
        builder->get()->CreateStore(irExpressionValue, _irValue->getValue());
    }
}

IRNodeType IRVariableDeclarationNode::getNodeType() {
    return IR_VARIABLE_DECLARATION_NODE;
}

std::string IRVariableDeclarationNode::toString() {
    return "IR_VARIABLE_DECLARATION_NODE";
}

void IRVariableDeclarationNode::print(std::unique_ptr<llvm::raw_fd_ostream> *stream) {
    _irValue->print(stream);
    stream->get()->write('\n');
    _irExpression->print(stream);
}