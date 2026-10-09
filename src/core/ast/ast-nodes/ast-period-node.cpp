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

#include "ast-period-node.h"
#include "ast-class-nodes/ast-this-access-node.h"

std::shared_ptr<ASTNode> ASTPeriodNode::transformIfNecessary(std::optional<std::shared_ptr<ASTNode>> prevNode, std::optional<std::shared_ptr<ASTNode>> nextNode, SyntaxAnalyzerMode mode) {
    if (prevNode && prevNode.value()->is(AST_THIS_NODE)) {
        return std::make_shared<ASTThisAccessNode>(_lexeme);
    }
    return shared_from_this();
}

ASTNodeType ASTPeriodNode::getNodeType() {
    return AST_PERIOD_NODE;
}

std::string ASTPeriodNode::toString() {
    return "PERIOD";
}
