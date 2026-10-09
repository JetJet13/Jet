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
// Created by Johny Georges on 2024-06-01.
//

#include "import-many-by-wildcard-module-declaration-reducer-strategy.h"
#include "../../../../../ast/ast-nodes/ast-declaration-nodes/ast-import-many-by-wildcard-module-declaration-node.h"

std::shared_ptr<ASTNode> ImportManyByWildcardModuleDeclarationReducerStrategy::execute(std::vector<std::shared_ptr<ASTNode>> nodes) {
    if (nodes.size() != 4) {
        throw std::invalid_argument("unable to reduce to import many module declaration since nodes list is not 4");
    }

    return std::make_shared<ASTImportManyByWildcardModuleDeclarationNode>(
        std::dynamic_pointer_cast<ASTImportNode>(nodes[0]),
        std::dynamic_pointer_cast<ASTImportModuleListByWildcardItemNode>(nodes[1]),
        std::dynamic_pointer_cast<ASTFromNode>(nodes[2]),
        std::dynamic_pointer_cast<ASTImportPathNode>(nodes[3])
    );


}