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
// Created by Johny Georges on 2024-07-08.
//

#include "ir-function-declaration-node.h"
#include "../../../core/pre-processor/semantic-analyzer/types/function-id-generator/function-id-generator.h"

IRFunctionDeclarationNode::IRFunctionDeclarationNode(std::shared_ptr<ASTFunctionDeclarationNode> node, llvm::Function* irValue, std::shared_ptr<IRFunctionParameterListNode> irParameterList, std::shared_ptr<IRBlockNode> irBlock, std::shared_ptr<IRInstructionNode> globalVariable) {
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

std::shared_ptr<IRFunctionParameterListNode> IRFunctionDeclarationNode::getParameters() {
    return _irParameterList;
}

std::shared_ptr<IRInstructionNode> IRFunctionDeclarationNode::getGlobalVariable() {
    return _globalVariable;
}

std::shared_ptr<IRBlockNode> IRFunctionDeclarationNode::getBlock() {
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