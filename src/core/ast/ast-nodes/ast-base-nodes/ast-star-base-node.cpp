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
// Created by Johny Georges on 2024-04-13.
//

#include "ast-star-base-node.h"
#include "../../../../shared/utils/logger/logger.h"
#include "../ast-operator-nodes/ast-unary-operators/ast-unary-operator-node.h"
#include "../ast-operator-nodes/ast-binary-operators/ast-binary-arithmetic-operator-node.h"
#include "../ast-import-nodes/ast-import-list-items/ast-import-module-list-wildcard-item-node.h"
#include "../ast-import-nodes/ast-import-wildcard-node.h"

ASTStarBaseNode::ASTStarBaseNode(std::shared_ptr<Lexeme> lexeme) {
    _lexeme = lexeme;
}

std::shared_ptr<ASTNode> ASTStarBaseNode::transformIfNecessary(std::optional<std::shared_ptr<ASTNode>> prevNode, std::optional<std::shared_ptr<ASTNode>> nextNode, SyntaxAnalyzerMode mode) {
    if (prevNode && prevNode.value()->is(AST_MODULE_ACCESS_NODE)) {
        return std::make_shared<ASTImportWildcardNode>(_lexeme);
    }

    if (mode == SA_IMPORT_MODULE_LIST_MODE) {
        return std::make_shared<ASTImportModuleListWildcardItemNode>(_lexeme);
    }

    return std::make_shared<ASTBinaryArithmeticOperatorNode>(_lexeme);
}

ASTNodeType ASTStarBaseNode::getNodeType() {
    return AST_STAR_BASE_NODE;
}

std::string ASTStarBaseNode::toString() {
    return "STAR_BASE";
}
