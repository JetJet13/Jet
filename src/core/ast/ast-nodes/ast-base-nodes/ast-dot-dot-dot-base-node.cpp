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
// Created by Johny Georges on 2024-04-12.
//

#include "ast-dot-dot-dot-base-node.h"
#include "../../../../shared/utils/logger/logger.h"
#include "../ast-module-nodes/ast-module-spread-node.h"

ASTDotDotDotBaseNode::ASTDotDotDotBaseNode(std::shared_ptr<Lexeme> lexeme) {
    _lexeme = lexeme;
}

std::shared_ptr<Lexeme> ASTDotDotDotBaseNode::getLexeme() {
    return _lexeme;
}

std::shared_ptr<ASTNode> ASTDotDotDotBaseNode::transformIfNecessary(std::optional<std::shared_ptr<ASTNode>> prevNode, std::optional<std::shared_ptr<ASTNode>> nextNode, SyntaxAnalyzerMode mode) {
    if (mode == SA_MODULE_LIST_MODE || mode == SA_IMPORT_MODULE_LIST_MODE) {
        return std::make_shared<ASTModuleSpreadNode>(_lexeme);
    }

    return shared_from_this();
}

ASTNodeType ASTDotDotDotBaseNode::getNodeType() {
    return AST_DOT_DOT_DOT_BASE_NODE;
}

std::string ASTDotDotDotBaseNode::toString() {
    return "DOT_DOT_DOT_BASE";
}

bool ASTDotDotDotBaseNode::isSameAs(std::shared_ptr<ASTNode> other) {
    if (!other->is(this->getNodeType())){
        return false;
    }
    auto otherNode = std::dynamic_pointer_cast<ASTDotDotDotBaseNode>(other);
    return this->getLexeme()->hasSameSymbolTypeAs(otherNode->getLexeme());
}

void ASTDotDotDotBaseNode::print() {
    Logger::log(this->toString(), "-", _lexeme->toString());
}