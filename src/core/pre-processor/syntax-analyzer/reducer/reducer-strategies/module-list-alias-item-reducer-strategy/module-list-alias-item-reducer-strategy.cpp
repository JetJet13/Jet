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
// Created by Johny Georges on 2024-04-13.
//

#include "module-list-alias-item-reducer-strategy.h"
#include "../../../../../ast/ast-nodes/ast-module-nodes/ast-module-list-items/ast-module-list-alias-item-node.h"

std::shared_ptr<ASTNode> ModuleListAliasItemReducerStrategy::execute(std::vector<std::shared_ptr<ASTNode>> nodes) {
    if (nodes.size() != 3) {
        throw std::invalid_argument("unable to reduce to module list alias item since nodes list is not of size 3");
    }

    return std::make_shared<ASTModuleListAliasItemNode>(
            std::dynamic_pointer_cast<ASTModuleNameNode>(nodes[0]),
            std::dynamic_pointer_cast<ASTAsNode>(nodes[1]),
            std::dynamic_pointer_cast<ASTModuleAliasNameNode>(nodes[2])
    );
}