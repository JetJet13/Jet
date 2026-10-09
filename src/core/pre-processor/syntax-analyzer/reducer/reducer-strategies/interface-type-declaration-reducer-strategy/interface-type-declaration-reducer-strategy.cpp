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
// Created by Johny Georges on 2025-06-25.
//

#include "interface-type-declaration-reducer-strategy.h"
#include "../../../../../ast/ast-nodes/ast-type-declaration-nodes/ast-interface-type-declaration-node.h"

std::shared_ptr<ASTNode> InterfaceTypeDeclarationReducerStrategy::execute(std::vector<std::shared_ptr<ASTNode>> nodes) {
    if (nodes.size() != 2 && nodes.size() != 3) {
        throw std::invalid_argument("unable to reduce to interface type declaration since nodes list is not of size 2 or 3");
    }

    if (nodes.size() == 2) {
        return std::make_shared<ASTInterfaceTypeDeclarationNode>(
                std::dynamic_pointer_cast<ASTInterfaceDefinitionNode>(nodes[0]),
                std::dynamic_pointer_cast<ASTInterfacePropertyListNode>(nodes[1])
        );
    }

    return std::make_shared<ASTInterfaceTypeDeclarationNode>(
            std::dynamic_pointer_cast<ASTInterfaceDefinitionNode>(nodes[1]),
            std::dynamic_pointer_cast<ASTInterfacePropertyListNode>(nodes[2]),
            std::dynamic_pointer_cast<ASTExportNode>(nodes[0])
    );
}