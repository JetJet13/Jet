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

#include "if-block-reducer-strategy.h"
#include "../../../../../ast/ast-nodes/ast-control-flow-nodes/ast-if-block-node.h"

std::shared_ptr<ASTNode> IfBlockReducerStrategy::execute(std::vector<std::shared_ptr<ASTNode>> nodes) {
    if (nodes.size() != 3) {
        throw std::invalid_argument("unable to reduce to if block since nodes list is not of size 3");
    }

    return std::make_shared<ASTIfBlockNode>(
            std::dynamic_pointer_cast<ASTIfNode>(nodes[0]),
            std::dynamic_pointer_cast<ASTControlFlowConditionNode>(nodes[1]),
            std::dynamic_pointer_cast<ASTControlFlowBlockNode>(nodes[2])
    );
}