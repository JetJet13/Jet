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
// Created by Johny Georges on 2024-04-02.
//

#include "try-statement-reducer-strategy.h"
#include "../../../../../ast/ast-nodes/ast-control-flow-nodes/try-catch-finally/ast-finally-block-node.h"
#include "../../../../../ast/ast-nodes/ast-statement-nodes/ast-try-statement-node.h"

std::shared_ptr<ASTNode> TryStatementReducerStrategy::execute(std::vector<std::shared_ptr<ASTNode>> nodes) {

    if (nodes.size() == 3) {
        return std::make_shared<ASTTryStatementNode>(
                std::dynamic_pointer_cast<ASTTryBlockNode>(nodes[0]),
                std::dynamic_pointer_cast<ASTCatchBlockNode>(nodes[1]),
                std::dynamic_pointer_cast<ASTFinallyBlockNode>(nodes[2])
        );
    }

    if (nodes.size() == 2) {
        return std::make_shared<ASTTryStatementNode>(
                std::dynamic_pointer_cast<ASTTryBlockNode>(nodes[0]),
                std::dynamic_pointer_cast<ASTCatchBlockNode>(nodes[1])
        );
    }

    throw std::invalid_argument("unable to reduce to try statement since nodes list is not of size 2 or 3");
}