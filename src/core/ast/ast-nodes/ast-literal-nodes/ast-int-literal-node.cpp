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

#include "ast-int-literal-node.h"
#include "../ast-tuple-nodes/ast-tuple-access-node.h"

std::shared_ptr<ASTNode> ASTIntLiteralNode::transformIfNecessary(std::optional<std::shared_ptr<ASTNode>> prevNode, std::optional<std::shared_ptr<ASTNode>> nextNode, SyntaxAnalyzerMode mode) {
    if (prevNode && prevNode.value()->is(AST_PERIOD_NODE)) {
        return (std::make_shared<ASTTupleAccessNode>(_lexeme))->setIndexValue(this->getValue());
    }

    return shared_from_this();
}

ASTNodeType ASTIntLiteralNode::getNodeType() {
    return AST_INT_LITERAL_NODE;
}

std::string ASTIntLiteralNode::toString() {
    return "INT_LITERAL - " + _lexeme->toString();
}

void ASTIntLiteralNode::setValue(std::shared_ptr<TokenTable> tokenTable) {
    _value = tokenTable->getInt(_lexeme->getToken()->getValueId().value());
}

std::string ASTIntLiteralNode::getValue() {
    return _value;
}
