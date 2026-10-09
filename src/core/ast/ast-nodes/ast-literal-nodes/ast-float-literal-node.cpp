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

#include "ast-float-literal-node.h"

ASTNodeType ASTFloatLiteralNode::getNodeType() {
    return AST_FLOAT_LITERAL_NODE;
}

std::string ASTFloatLiteralNode::toString() {
    return "FLOAT_LITERAL - " + _lexeme->toString();
}

void ASTFloatLiteralNode::setValue(std::shared_ptr<TokenTable> tokenTable) {
    _value = tokenTable->getFloat(_lexeme->getToken()->getValueId().value());
}

std::string ASTFloatLiteralNode::getValue() {
    return _value;
}