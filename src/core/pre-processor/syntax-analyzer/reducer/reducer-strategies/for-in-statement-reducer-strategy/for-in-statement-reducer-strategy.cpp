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
// Created by Johny Georges on 2024-03-29.
//

#include "for-in-statement-reducer-strategy.h"
#include "../../../../../ast/ast-nodes/ast-statement-nodes/ast-for-in-statement-node.h"

std::shared_ptr<ASTNode> ForInStatementReducerStrategy::execute(std::vector<std::shared_ptr<ASTNode>> nodes) {
    if (nodes.size() != 5) {
        throw std::invalid_argument("unable to reduce to for-in statement since nodes list is not 5");
    }

    return std::make_shared<ASTForInStatementNode>(
            std::dynamic_pointer_cast<ASTForNode>(nodes[0]),
            std::dynamic_pointer_cast<ASTForInVariableNode>(nodes[1]),
            std::dynamic_pointer_cast<ASTForInNode>(nodes[2]),
            std::dynamic_pointer_cast<ASTForInSourceNode>(nodes[3]),
            std::dynamic_pointer_cast<ASTControlFlowBlockNode>(nodes[4])
    );
}