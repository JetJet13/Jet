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
// Created by Johny Georges on 2025-07-05.
//

#include "implements-interface-list-reducer-strategy.h"
#include "../../../../../ast/ast-nodes/ast-interface-nodes/ast-implements-interface-list-node.h"
#include "../../../../../ast/ast-nodes/ast-interface-nodes/ast-implements-interface-name-last-node.h"

std::shared_ptr<ASTNode> ImplementsInterfaceListReducerStrategy::execute(std::vector<std::shared_ptr<ASTNode>> nodes) {
    auto implementsInterfaceListNode = std::make_shared<ASTImplementsInterfaceListNode>(std::dynamic_pointer_cast<ASTImplementsNode>(nodes[0]));
    for (uint64_t i = 1; i < nodes.size() - 1; ++i) {
        auto node = nodes[i];
        if (i % 2 == 1 && node->is(AST_IMPLEMENTS_INTERFACE_NAME_NODE)) {
            implementsInterfaceListNode->addInterface(std::dynamic_pointer_cast<ASTImplementsInterfaceNameNode>(node));
        } else if (i % 2 == 0 && node->is(AST_COMMA_NODE)) {
            implementsInterfaceListNode->addComma(std::dynamic_pointer_cast<ASTCommaNode>(node));
        } else {
            throw std::invalid_argument("unable to reduce to implements interface list since node list is malformed");
        }
    }

    implementsInterfaceListNode
    ->addInterface((std::dynamic_pointer_cast<ASTImplementsInterfaceNameLastNode>(nodes[nodes.size() - 1]))->convertToInterfaceName());

    return implementsInterfaceListNode;
}