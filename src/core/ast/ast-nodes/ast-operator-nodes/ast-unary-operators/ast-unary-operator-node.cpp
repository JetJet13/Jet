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
// Created by Johny Georges on 2024-02-20.
//

#include "./ast-unary-operator-node.h"
#include "../../../../../shared/utils/logger/logger.h"

bool ASTUnaryOperatorNode::isPlus() {
    return _lexeme->getToken()->getSymbol()->isPlus();
}

bool ASTUnaryOperatorNode::isMinus() {
    return _lexeme->getToken()->getSymbol()->isMinus();
}

bool ASTUnaryOperatorNode::isBang() {
    return _lexeme->getToken()->getSymbol()->isBang();
}

ASTNodeType ASTUnaryOperatorNode::getNodeType() {
    return AST_UNARY_OPERATOR_NODE;
}

std::string ASTUnaryOperatorNode::toString() {
    return "UNARY_OPERATOR";
}