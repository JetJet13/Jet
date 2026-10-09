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
// Created by Johny Georges on 2024-02-17.
//

#include "variable-init-reducer-strategy.h"
#include "../../../../../ast/ast-nodes/ast-variable-nodes/ast-variable-init-node.h"
#include "../../../../../ast/ast-nodes/ast-variable-nodes/ast-variable-definition-node.h"

std::shared_ptr<ASTNode> VariableInitReducerStrategy::execute(std::vector<std::shared_ptr<ASTNode>> nodes) {
    if (nodes.size() == 2) {
        return std::make_shared<ASTVariableInitNode>(
                (std::dynamic_pointer_cast<ASTVariableDefinitionNode>(nodes[0]))->getVarTypeNode(),
                (std::dynamic_pointer_cast<ASTVariableDefinitionNode>(nodes[0]))->getIdentifierNode(),
                std::dynamic_pointer_cast<ASTAssignmentOperatorNode>(nodes[1])
        );
    }

    if (nodes.size() == 4) {
        return std::make_shared<ASTVariableInitNode>(
                (std::dynamic_pointer_cast<ASTVariableDefinitionNode>(nodes[0]))->getVarTypeNode(),
                (std::dynamic_pointer_cast<ASTVariableDefinitionNode>(nodes[0]))->getIdentifierNode(),
                std::dynamic_pointer_cast<ASTAssignmentOperatorNode>(nodes[3]),
                std::dynamic_pointer_cast<ASTTypeColonNode>(nodes[1]),
                std::dynamic_pointer_cast<ASTTypeNode>(nodes[2])
        );
    }

    throw std::invalid_argument("unable to reduce to var init node since nodes list is not 2 or 4");
}
