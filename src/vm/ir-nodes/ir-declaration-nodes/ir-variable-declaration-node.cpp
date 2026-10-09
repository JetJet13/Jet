// Copyright 2026 Johny Georges
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

//
// Created by Johny Georges on 2024-07-01.
//

#include "ir-variable-declaration-node.h"

IRVariableDeclarationNode::IRVariableDeclarationNode(std::shared_ptr<ASTVariableDeclarationNode> astNode, std::shared_ptr<IRInstructionNode> irValue, std::shared_ptr<IRExpressionNode> irExpression, llvm::Value* variableNameIRValue, std::optional<std::shared_ptr<IRInstructionNode>> irGlobalVariable, std::optional<std::shared_ptr<IRInstructionNode>> irArc) {
    _node = astNode;
    _irValue = irValue;
    _irExpression = irExpression;
    _variableNameIRValue = variableNameIRValue;
    _irGlobalVariable = irGlobalVariable;
    _irArc = irArc;
}

std::string IRVariableDeclarationNode::getVariableName() {
    return _node->getId();
}

llvm::Value* IRVariableDeclarationNode::getVariableNameIRValue() {
    return _variableNameIRValue;
}

llvm::Value* IRVariableDeclarationNode::getValue() {
    return _irValue->getValue();
}

llvm::Type* IRVariableDeclarationNode::getAllocatedType() {
    return _irValue->getAllocatedType();
}

std::shared_ptr<IRType> IRVariableDeclarationNode::getAllocatedIRType() {
    return _irValue->getIRType()->getSourceType();
}

std::shared_ptr<IRInstructionNode> IRVariableDeclarationNode::getIRValue() {
    return _irValue;
}

std::shared_ptr<IRExpressionNode> IRVariableDeclarationNode::getIRExpression() {
    return _irExpression;
}

bool IRVariableDeclarationNode::toBeFreedDirectly() {
    return !_node->isCaptured() &&
    !_node->isGlobal() &&
    _irValue->getIRType()->containsTypeThatRequiresFreeing();
}

bool IRVariableDeclarationNode::isLambdaVariable() {
    return _irExpression->getIRType()->getUnderlyingType()->isLambdaType();
}

std::optional<std::shared_ptr<IRInstructionNode>> IRVariableDeclarationNode::getGlobalVariable() {
    return _irGlobalVariable;
}

std::optional<std::shared_ptr<IRInstructionNode>> IRVariableDeclarationNode::getArc() {
    return _irArc;
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