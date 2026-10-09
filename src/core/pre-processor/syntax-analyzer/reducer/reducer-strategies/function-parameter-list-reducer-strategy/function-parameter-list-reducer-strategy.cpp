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
// Created by Johny Georges on 2024-03-19.
//

#include "function-parameter-list-reducer-strategy.h"
#include "../../../../../ast/ast-nodes/ast-function-nodes/ast-function-parameter-list-node.h"

std::shared_ptr<ASTNode> FunctionParameterListReducerStrategy::execute(std::vector<std::shared_ptr<ASTNode>> nodes) {
    auto functionParameterListNode = std::make_shared<ASTFunctionParameterListNode>(
            std::dynamic_pointer_cast<ASTFunctionParameterListStartNode>(nodes[0]),
            std::dynamic_pointer_cast<ASTFunctionParameterListEndNode>(nodes[nodes.size() - 1])
    );

    for (uint64_t i = 1; i < nodes.size() - 1; ++i) {
        auto node = nodes[i];
        if (i % 2 == 1 && node->is(AST_FUNCTION_PARAMETER_NODE)) {
            functionParameterListNode->addParameter(std::dynamic_pointer_cast<ASTFunctionParameterNode>(node));
        } else if (i % 2 == 0 && node->is(AST_COMMA_NODE) && i != nodes.size() - 2) {
            functionParameterListNode->addComma(std::dynamic_pointer_cast<ASTCommaNode>(node));
        } else {
            throw std::invalid_argument("unable to reduce to function parameter list since node list is malformed");
        }
    }

    return functionParameterListNode;
}