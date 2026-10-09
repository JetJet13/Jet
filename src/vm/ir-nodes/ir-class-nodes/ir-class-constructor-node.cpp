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
// Created by Johny Georges on 2024-12-09.
//

#include "ir-class-constructor-node.h"

IRClassConstructorNode::IRClassConstructorNode(std::shared_ptr<ASTClassConstructorDeclarationNode> node, llvm::Function* irValue, std::shared_ptr<IRFunctionParameterListNode> irParameters, std::shared_ptr<IRBlockNode> irBlock) {
    _node = node;
    _irValue = irValue;
    _irParameters = irParameters;
    _irBlock = irBlock;
}

std::shared_ptr<ASTClassConstructorDeclarationNode> IRClassConstructorNode::getNode() {
    return _node;
}

llvm::Function* IRClassConstructorNode::getFunction() {
    return _irValue;
}

std::shared_ptr<IRFunctionParameterListNode> IRClassConstructorNode::getParameters() {
    return _irParameters;
}

std::shared_ptr<IRBlockNode> IRClassConstructorNode::getBlock() {
    return _irBlock;
}