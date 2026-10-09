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

#include "ast-else-if-node.h"
#include "../../../../shared/utils/logger/logger.h"
#include "../../types/source-code-builder/source-code-builder.h"

ASTElseIfNode::ASTElseIfNode(std::shared_ptr<ASTElseNode> elseKeyword, std::shared_ptr<ASTIfNode> ifKeyword) {
    _else = elseKeyword;
    _if = ifKeyword;
}

std::shared_ptr<ASTElseNode> ASTElseIfNode::getElse() {
    return _else;
}

std::shared_ptr<ASTIfNode> ASTElseIfNode::getIf() {
    return _if;
}

std::shared_ptr<Position> ASTElseIfNode::getStartPosition() {
    return _else->getStartPosition();
}

std::shared_ptr<Position> ASTElseIfNode::getEndPosition() {
    return _if->getEndPosition();
}

ASTNodeType ASTElseIfNode::getNodeType() {
    return AST_ELSE_IF_NODE;
}

std::string ASTElseIfNode::toString() {
    return "ELSE_IF";
}

bool ASTElseIfNode::isSameAs(std::shared_ptr<ASTNode> other) {
    if (!other->is(this->getNodeType())){
        return false;
    }
    auto otherNode = std::dynamic_pointer_cast<ASTElseIfNode>(other);
    return this->getElse()->isSameAs(otherNode->getElse()) &&
           this->getIf()->isSameAs(otherNode->getIf());
}

void ASTElseIfNode::print() {
    Logger::log("----------", this->toString(), "----------");
    _else->print();
    _if->print();
    Logger::log("----------");
}

std::string ASTElseIfNode::toSourceCode() {
    auto sourceCodeBuilder = SourceCodeBuilder();
    sourceCodeBuilder.add(_else)
    ->add(_if);
    return sourceCodeBuilder.build();
}