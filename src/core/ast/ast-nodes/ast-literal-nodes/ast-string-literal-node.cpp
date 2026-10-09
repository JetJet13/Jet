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
// Created by Johny Georges on 2024-01-13.
//

#include "ast-string-literal-node.h"
#include "../ast-import-nodes/ast-import-path-node.h"

std::shared_ptr<ASTNode> ASTStringLiteralNode::transformIfNecessary(std::optional<std::shared_ptr<ASTNode>> prevNode, std::optional<std::shared_ptr<ASTNode>> nextNode, SyntaxAnalyzerMode mode) {

    if (prevNode && prevNode.value()->is(AST_FROM_NODE)) {
        return std::make_shared<ASTImportPathNode>(std::dynamic_pointer_cast<ASTStringLiteralNode>(shared_from_this()));
    }

    return shared_from_this();
}

ASTNodeType ASTStringLiteralNode::getNodeType() {
    return AST_STRING_LITERAL_NODE;
}

std::string ASTStringLiteralNode::toString() {
    return "STRING_LITERAL - " + _lexeme->toString();
}

void ASTStringLiteralNode::setValue(std::shared_ptr<TokenTable> tokenTable) {
    _value = tokenTable->getString(_lexeme->getToken()->getValueId().value());
}


std::string ASTStringLiteralNode::getValue() {
    return _value;
}

std::string ASTStringLiteralNode::toSourceCode() {
    return "\"" + _lexeme->getToken()->getRawValue() + "\"";
}