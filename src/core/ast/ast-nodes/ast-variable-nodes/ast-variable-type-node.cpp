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
// Created by Johny Georges on 2024-02-08.
//

#include "ast-variable-type-node.h"

bool ASTVariableTypeNode::isConst() {
    return _lexeme->getToken()->getSymbolType() == SYM_CONST;
}

ASTNodeType ASTVariableTypeNode::getNodeType() {
    return AST_VARIABLE_TYPE_NODE;
}

std::string ASTVariableTypeNode::toString() {
    return "VARIABLE_TYPE";
}
