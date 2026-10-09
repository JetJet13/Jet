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
// Created by Johny Georges on 2024-03-09.
//

#include "array-node-reducer-strategy.h"
#include "../../../../../ast/ast-nodes/ast-array-nodes/ast-array-node.h"


std::shared_ptr<ASTNode> ArrayNodeReducerStrategy::execute(std::vector<std::shared_ptr<ASTNode>> nodes) {
    auto arrayNode = std::make_shared<ASTArrayNode>(std::dynamic_pointer_cast<ASTLeftBracketNode>(nodes[0]), std::dynamic_pointer_cast<ASTRightBracketNode>(nodes[nodes.size() - 1]));

    for (uint64_t i = 1; i < nodes.size() - 1; ++i) {
        auto node = nodes[i];
        if (i % 2 == 1 && node->isExpression()) {
            arrayNode->addElement(std::dynamic_pointer_cast<ASTExpressionNode>(node));
        } else if (i % 2 == 0 && node->is(AST_COMMA_NODE) && i != nodes.size() - 2) {
            arrayNode->addComma(std::dynamic_pointer_cast<ASTCommaNode>(node));
        } else {
            throw std::invalid_argument("unable to reduce to array node since node list is malformed");
        }
    }
    return arrayNode;
}