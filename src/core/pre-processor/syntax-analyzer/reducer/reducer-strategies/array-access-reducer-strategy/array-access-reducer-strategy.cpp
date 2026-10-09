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
// Created by Johny Georges on 2024-03-12.
//

#include "array-access-reducer-strategy.h"
#include "../../../../../ast/ast-nodes/ast-array-nodes/ast-array-access-node.h"
#include "../../../../../ast/ast-nodes/ast-array-nodes/ast-array-node.h"

std::shared_ptr<ASTNode> ArrayAccessReducerStrategy::execute(std::vector<std::shared_ptr<ASTNode>> nodes) {
    if (nodes.size() != 1 || !nodes[0]->is(AST_ARRAY_NODE)) {
        throw std::invalid_argument("unable to reduce to array access node since node list != 1 or nodes[0] is not an instance of array base node");
    }
    auto arrayNode = std::dynamic_pointer_cast<ASTArrayNode>(nodes[0]);
    if (!arrayNode->getFirstElement()) {
        throw std::invalid_argument("unable to reduce to array access node since array base node has no elements");
    }
    auto index = std::dynamic_pointer_cast<ASTExpressionNode>(arrayNode->getFirstElement().value());
    return std::make_shared<ASTArrayAccessNode>(arrayNode->getLeftBracket(), index, arrayNode->getRightBracket());
}