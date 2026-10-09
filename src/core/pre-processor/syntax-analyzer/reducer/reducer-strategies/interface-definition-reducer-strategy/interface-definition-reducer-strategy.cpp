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

#include "interface-definition-reducer-strategy.h"
#include "../../../../../ast/ast-nodes/ast-interface-nodes/ast-interface-definition-node.h"

std::shared_ptr<ASTNode> InterfaceDefinitionReducerStrategy::execute(std::vector<std::shared_ptr<ASTNode>> nodes) {
    if (nodes.size() != 2) {
        throw std::invalid_argument("unable to reduce to interface definition since nodes list is not of size 2");
    }

    return std::make_shared<ASTInterfaceDefinitionNode>(
            std::dynamic_pointer_cast<ASTInterfaceNode>(nodes[0]),
            std::dynamic_pointer_cast<ASTInterfaceNameNode>(nodes[1])
    );
}