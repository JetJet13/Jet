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
// Created by Johny Georges on 2024-06-03.
//

#include "scope.h"

Scope::Scope(std::shared_ptr<ASTBlockStartNode> blockStartNode) {
    _blockStartNode = blockStartNode;
    _block = std::vector<std::shared_ptr<ASTNode>>();
}

void Scope::add(std::shared_ptr<ASTNode> node) {
    _block.push_back(node);
}

std::vector<std::shared_ptr<ASTNode>> Scope::getBlock() {
    return _block;
}

std::shared_ptr<ASTBlockNode> Scope::convertToBlockNode(std::shared_ptr<ASTBlockEndNode> blockEndNode) {
    return std::make_shared<ASTBlockNode>(_blockStartNode, _block, blockEndNode);
}

std::stack<std::shared_ptr<ASTNode>> Scope::convertToStack() {
    auto nodeStack = std::stack<std::shared_ptr<ASTNode>>();
    nodeStack.push(_blockStartNode);
    for (auto node : _block) {
        nodeStack.push(node);
    }
    return nodeStack;
}