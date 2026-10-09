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
// Created by Johny Georges on 2024-03-28.
//

#include "ast-null-node.h"
#include "../../../shared/utils/logger/logger.h"

ASTNodeType ASTNullNode::getNodeType() {
    return AST_NULL_NODE;
}

std::string ASTNullNode::toString() {
    return "NULL";
}

std::shared_ptr<Position> ASTNullNode::getStartPosition() {
    return std::make_shared<Position>();
}

std::shared_ptr<Position> ASTNullNode::getEndPosition() {
    return std::make_shared<Position>();
}

bool ASTNullNode::isSameAs(std::shared_ptr<ASTNode> other) {
    return !other->is(this->getNodeType());
}

void ASTNullNode::print() {
    Logger::log(this->toString());
}