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
// Created by Johny Georges on 2024-03-28.
//

#include "if-statement-reducer-strategy.h"
#include "../../../../../ast/ast-nodes/ast-statement-nodes/ast-if-statement-node.h"

std::shared_ptr<ASTNode> IfStatementReducerStrategy::execute(std::vector<std::shared_ptr<ASTNode>> nodes) {
    if (nodes.empty()) {
        throw std::logic_error("NO NODES!");
    }
    auto elseIfBlocks = std::vector<std::shared_ptr<ASTElseIfBlockNode>>();
    auto elseBlock = std::optional<std::shared_ptr<ASTElseBlockNode>>();
    for (uint64_t i = 1; i < nodes.size() ; i++) {
        if (nodes[i]->is(AST_ELSE_IF_BLOCK_NODE)) {
            elseIfBlocks.push_back(std::dynamic_pointer_cast<ASTElseIfBlockNode>(nodes[i]));
        }
        if (nodes[i]->is(AST_ELSE_BLOCK_NODE)) {
            elseBlock = std::dynamic_pointer_cast<ASTElseBlockNode>(nodes[i]);
        }
    }

    return std::make_shared<ASTIfStatementNode>(
            std::dynamic_pointer_cast<ASTIfBlockNode>(nodes[0]),
            elseIfBlocks,
            elseBlock
    );
}