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
// Created by Johny Georges on 2024-03-26.
//

#include "tuple-access-expression-reducer-strategy.h"
#include "../../../../../ast/ast-nodes/ast-expression-nodes/ast-tuple-access-expression.h"
#include "../../../../../ast/ast-nodes/ast-period-node.h"

std::shared_ptr<ASTNode> TupleAccessExpressionReducerStrategy::execute(std::vector<std::shared_ptr<ASTNode>> nodes) {
    if (nodes.size() != 3) {
        throw std::invalid_argument("unable to reduce to tuple access expression since nodes list is not 3");
    }

    return std::make_shared<ASTTupleAccessExpressionNode>(
            std::dynamic_pointer_cast<ASTObjectAccessSourceNode>(nodes[0]),
            std::dynamic_pointer_cast<ASTPeriodNode>(nodes[1]),
            std::dynamic_pointer_cast<ASTTupleAccessNode>(nodes[2])
    );
}