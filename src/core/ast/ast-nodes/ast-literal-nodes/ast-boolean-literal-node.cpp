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

#include "ast-boolean-literal-node.h"
#include "../../../../shared/utils/logger/logger.h"

ASTNodeType ASTBooleanLiteralNode::getNodeType() {
    return AST_BOOLEAN_LITERAL_NODE;
}

std::string ASTBooleanLiteralNode::toString() {
    return "BOOLEAN_LITERAL - " + _lexeme->toString();
}

void ASTBooleanLiteralNode::setValue(std::shared_ptr<TokenTable> tokenTable) {
    if (_lexeme->getToken()->getSymbol()->isTrue()) {
        _value = true;
        return;
    } else if (_lexeme->getToken()->getSymbol()->isFalse()) {
        _value = false;
        return;
    }

    throw std::logic_error("unable to set value for boolean literal node because lexeme is not true or false");
}

bool ASTBooleanLiteralNode::getValue() {
    return _value;
}
