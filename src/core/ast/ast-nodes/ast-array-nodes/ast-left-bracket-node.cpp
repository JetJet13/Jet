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
// Created by Johny Georges on 2024-03-09.
//

#include "ast-left-bracket-node.h"
#include "../ast-type-nodes/ast-array-type-nodes/ast-array-type-start-node.h"

std::shared_ptr<ASTNode> ASTLeftBracketNode::transformIfNecessary(std::optional<std::shared_ptr<ASTNode>> prevNode, std::optional<std::shared_ptr<ASTNode>> nextNode, SyntaxAnalyzerMode mode) {
    if (mode == SA_TYPE_PARAMETER_LIST_MODE ||
        mode == SA_FUNCTION_PARAMETER_LIST_MODE ||
        (prevNode &&
         prevNode.value()->isOneOf({
             AST_TYPE_COLON_NODE,
             AST_STRUCT_TYPE_COLON_NODE,
             AST_FUNCTION_PARAMETER_LIST_NODE,
             AST_TYPE_PARAMETER_LIST_START_NODE,
             AST_TYPE_ASSIGNMENT_OPERATOR_NODE,
             AST_INTERFACE_COLON_NODE,
             AST_ARRAY_TYPE_START_NODE
         })
        )) {
        return std::make_shared<ASTArrayTypeStartNode>(this->getLexeme());
    }
    return shared_from_this();
}

ASTNodeType ASTLeftBracketNode::getNodeType() {
    return AST_LEFT_BRACKET_NODE;
}

std::string ASTLeftBracketNode::toString() {
    return "LEFT_BRACKET";
}

