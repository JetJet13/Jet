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
// Created by Johny Georges on 2026-05-30.
//

#include "ast-colon-colon-base-node.h"
#include "../ast-type-nodes/ast-module-type-nodes/ast-module-access-type-node.h"
#include "../ast-module-nodes/ast-module-access-node.h"

std::shared_ptr<ASTNode> ASTColonColonBaseNode::transformIfNecessary(std::optional<std::shared_ptr<ASTNode>> prevNode, std::optional<std::shared_ptr<ASTNode>> nextNode, SyntaxAnalyzerMode mode) {
    if (prevNode && prevNode.value()->is(AST_MODULE_TYPE_SOURCE_NODE)) {
        return std::make_shared<ASTModuleAccessTypeNode>(_lexeme);
    }

    return std::make_shared<ASTModuleAccessNode>(_lexeme);
}

ASTNodeType ASTColonColonBaseNode::getNodeType() {
    return AST_COLON_COLON_BASE_NODE;
}

std::string ASTColonColonBaseNode::toString() {
    return "COLON_COLON_BASE";
}