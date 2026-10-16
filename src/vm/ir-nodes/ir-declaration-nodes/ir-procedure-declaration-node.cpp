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
// Created by Johny Georges on 2024-07-13.
//

#include "ir-procedure-declaration-node.h"
#include "../../../core/pre-processor/semantic-analyzer/types/function-id-generator/function-id-generator.h"

IRProcedureDeclarationNode::IRProcedureDeclarationNode(std::shared_ptr<ASTProcedureDeclarationNode> node, llvm::Function* irValue, std::shared_ptr<IRFunctionParameterListNode> irParameterList, std::shared_ptr<IRBlockNode> irBlock, std::shared_ptr<IRInstructionNode> globalVariable) {
    _node = node;
    _irValue = irValue;
    _irParameterList = irParameterList;
    _irBlock = irBlock;
    _globalVariable = globalVariable;
}

std::string IRProcedureDeclarationNode::getName() {
    return _node->getId();
}

std::string IRProcedureDeclarationNode::getNormalizedName() {
    return _node->getId();
}

std::shared_ptr<IRFunctionParameterListNode> IRProcedureDeclarationNode::getParameters() {
    return _irParameterList;
}

std::shared_ptr<IRInstructionNode> IRProcedureDeclarationNode::getGlobalVariable() {
    return _globalVariable;
}

std::shared_ptr<IRBlockNode> IRProcedureDeclarationNode::getBlock() {
    return _irBlock;
}

llvm::Value* IRProcedureDeclarationNode::getValue() {
    return _irValue;
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