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
// Created by Johny Georges on 2024-04-16.
//

#include "import-module-list-spread-item-reducer-strategy.h"
#include "../../../../../ast/ast-nodes/ast-import-nodes/ast-import-list-items/ast-import-module-list-spread-item-node.h"

std::shared_ptr<ASTNode> ImportModuleListSpreadItemReducerStrategy::execute(std::vector<std::shared_ptr<ASTNode>> nodes) {
    if (nodes.size() != 2) {
        throw std::invalid_argument("unable to reduce to import module list spread item since nodes list is not of size 2");
    }

    return std::make_shared<ASTImportModuleListSpreadItemNode>(
            std::dynamic_pointer_cast<ASTImportSpreadNode>(nodes[0]),
            std::dynamic_pointer_cast<ASTImportModuleNameNode>(nodes[1])
    );
}