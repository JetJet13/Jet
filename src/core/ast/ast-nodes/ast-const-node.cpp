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
// Created by Johny Georges on 2024-04-20.
//

#include "ast-const-node.h"
#include "ast-variable-nodes/ast-variable-type-node.h"

std::shared_ptr<ASTNode> ASTConstNode::transformIfNecessary(std::optional<std::shared_ptr<ASTNode>> prevNode, std::optional<std::shared_ptr<ASTNode>> nextNode, SyntaxAnalyzerMode mode) {
    if (prevNode && prevNode.value()->isOneOf({ AST_STATIC_NODE, AST_PUBLIC_NODE, AST_PROTECTED_NODE, AST_PRIVATE_NODE })) {
        return shared_from_this();
    }
    return std::make_shared<ASTVariableTypeNode>(_lexeme);
}

ASTNodeType ASTConstNode::getNodeType() {
    return AST_CONST_NODE;
}

std::string ASTConstNode::toString() {
    return "CONST";
}