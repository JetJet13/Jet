//
// Created by Johny Georges on 2024-07-01.
//

#include "ir-variable-declaration-node.h"

IRVariableDeclarationNode::IRVariableDeclarationNode(ASTVariableDeclarationNode* astNode, IRInstructionNode* irValue, IRExpressionNode* irExpression, std::optional<IRGlobalVariableNode*> irGlobalVariable) {
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

IRInstructionNode* IRVariableDeclarationNode::getIRValue() {
    return _irValue;
}

IRExpressionNode* IRVariableDeclarationNode::getIRExpression() {
    return _irExpression;
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