//
// Created by Johny Georges on 2024-07-01.
//

#include "ir-variable-declaration-node.h"

IRVariableDeclarationNode::IRVariableDeclarationNode(ASTVariableDeclarationNode* astNode, IRInstructionNode* irValue, IRExpressionNode* irExpression, std::optional<IRInstructionNode*> irGlobalVariable) {
    _node = astNode;
    _irValue = irValue;
    _irExpression = irExpression;
    _irGlobalVariable = irGlobalVariable;
}



std::string IRVariableDeclarationNode::getVariableName() {
    return _node->getId();
}

llvm::Value* IRVariableDeclarationNode::getValue() {
    return _irValue->getValue();
}

llvm::Type* IRVariableDeclarationNode::getAllocatedType() {
    return _irValue->getAllocatedType();
}

IRType* IRVariableDeclarationNode::getAllocatedIRType() {
    return _irValue->getIRType()->getSourceType();
}

IRInstructionNode* IRVariableDeclarationNode::getIRValue() {
    return _irValue;
}

IRExpressionNode* IRVariableDeclarationNode::getIRExpression() {
    return _irExpression;
}

bool IRVariableDeclarationNode::needsToBeFreed() {
    return !_node->isReferenced() &&
    !_node->isCaptured() &&
    !_node->isGlobal() &&
    _irValue->getIRType()->containsTypeThatRequiresFreeing();
}

std::optional<IRInstructionNode*> IRVariableDeclarationNode::getGlobalVariable() {
    return _irGlobalVariable;
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