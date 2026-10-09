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
// Created by Johny Georges on 2026-03-14.
//

#include "ast-tuple-type-start-node.h"
#include "../ast-struct-type-nodes/ast-struct-type-start-node.h"

std::shared_ptr<ASTNode> ASTTupleTypeStartNode::transformIfNecessary(std::optional<std::shared_ptr<ASTNode>> prevNode, std::optional<std::shared_ptr<ASTNode>> nextNode, SyntaxAnalyzerMode mode) {
    if (mode == SA_STRUCT_TYPE_MODE) {
        return std::make_shared<ASTStructTypeStartNode>(this->getLexeme());
    }
    return shared_from_this();
}

ASTNodeType ASTTupleTypeStartNode::getNodeType() {
    return AST_TUPLE_TYPE_START_NODE;
}

std::string ASTTupleTypeStartNode::toString() {
    return "TUPLE_TYPE_START";
}