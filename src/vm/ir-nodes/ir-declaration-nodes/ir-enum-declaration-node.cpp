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
// Created by Johny Georges on 2024-07-15.
//

#include "ir-enum-declaration-node.h"

IREnumDeclarationNode::IREnumDeclarationNode(std::shared_ptr<ASTEnumDeclarationNode> node, std::shared_ptr<IRInstructionNode> irValue) {
    _node = node;
    _irValue = irValue;
}

llvm::Value* IREnumDeclarationNode::getValue() {
    return _irValue->getValue();
}

IRNodeType IREnumDeclarationNode::getNodeType() {
    return IR_ENUM_DECLARATION_NODE;
}

std::string IREnumDeclarationNode::toString() {
    return "IR_ENUM_DECLARATION_NODE";
}

void IREnumDeclarationNode::print(std::unique_ptr<llvm::raw_fd_ostream> *stream) {
    _irValue->print(stream);
}