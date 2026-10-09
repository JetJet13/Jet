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
// Created by Johny Georges on 2024-03-14.
//

#include "ast-colon-base-node.h"
#include "../ast-type-nodes/ast-type-colon-node.h"
#include "../ast-struct-nodes/ast-struct-colon-node.h"
#include "../ast-interface-nodes/ast-interface-colon-node.h"
#include "../ast-type-nodes/ast-struct-type-nodes/ast-struct-type-colon-node.h"

std::shared_ptr<ASTNode> ASTColonBaseNode::transformIfNecessary(std::optional<std::shared_ptr<ASTNode>> prevNode, std::optional<std::shared_ptr<ASTNode>> nextNode, SyntaxAnalyzerMode mode) {
    if (mode == SA_FUNCTION_PARAMETER_LIST_MODE ||
        mode == SA_GROUP_MODE ||
        (prevNode && prevNode.value()->isOneOf({ AST_VARIABLE_DEFINITION_NODE, AST_CLASS_PROPERTY_DEFINITION_NODE, AST_FUNCTION_PARAMETER_LIST_NODE }))) {
        return std::make_shared<ASTTypeColonNode>(_lexeme);
    }

    if (mode == SA_STRUCT_MODE) {
        return std::make_shared<ASTStructColonNode>(_lexeme);
    }

    if (mode == SA_INTERFACE_MODE) {
        return std::make_shared<ASTInterfaceColonNode>(_lexeme);
    }

    if (mode == SA_STRUCT_TYPE_MODE || mode == SA_TUPLE_TYPE_MODE) {
        return std::make_shared<ASTStructTypeColonNode>(_lexeme);
    }
    return shared_from_this();
}

ASTNodeType ASTColonBaseNode::getNodeType() {
    return AST_COLON_BASE_NODE;
}

std::string ASTColonBaseNode::toString() {
    return "COLON_BASE";
}