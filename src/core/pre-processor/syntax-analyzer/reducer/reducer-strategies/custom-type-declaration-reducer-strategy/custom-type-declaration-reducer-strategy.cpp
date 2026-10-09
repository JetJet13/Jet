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
// Created by Johny Georges on 2025-07-07.
//

#include "custom-type-declaration-reducer-strategy.h"
#include "../../../../../ast/ast-nodes/ast-type-declaration-nodes/ast-custom-type-declaration-node.h"

std::shared_ptr<ASTNode> CustomTypeDeclarationReducerStrategy::execute(std::vector<std::shared_ptr<ASTNode>> nodes) {
    if (nodes.size() != 4 && nodes.size() != 5) {
        throw std::invalid_argument("unable to reduce to custom type declaration since nodes list is not of size 4 or 5");
    }

    if (nodes.size() == 4) {
        return std::make_shared<ASTCustomTypeDeclarationNode>(
                std::dynamic_pointer_cast<ASTTypeKeywordNode>(nodes[0]),
                std::dynamic_pointer_cast<ASTTypeNameNode>(nodes[1]),
                std::dynamic_pointer_cast<ASTTypeAssignmentOperatorNode>(nodes[2]),
                std::dynamic_pointer_cast<ASTTypeNode>(nodes[3])
        );
    }

    return std::make_shared<ASTCustomTypeDeclarationNode>(
            std::dynamic_pointer_cast<ASTTypeKeywordNode>(nodes[1]),
            std::dynamic_pointer_cast<ASTTypeNameNode>(nodes[2]),
            std::dynamic_pointer_cast<ASTTypeAssignmentOperatorNode>(nodes[3]),
            std::dynamic_pointer_cast<ASTTypeNode>(nodes[4]),
            std::dynamic_pointer_cast<ASTExportNode>(nodes[0])
    );
}