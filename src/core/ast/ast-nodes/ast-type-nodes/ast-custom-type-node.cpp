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
// Created by Johny Georges on 2024-04-04.
//

#include "ast-custom-type-node.h"
#include "../../../../shared/utils/logger/logger.h"

ASTCustomTypeNode::ASTCustomTypeNode(std::shared_ptr<Lexeme> lexeme, std::string id) {
    _lexeme = lexeme;
    _id = id;
}

std::shared_ptr<Lexeme> ASTCustomTypeNode::getLexeme() {
    return _lexeme;
}

std::shared_ptr<Position> ASTCustomTypeNode::getStartPosition() {
    return _lexeme->getStartPosition();
}

std::shared_ptr<Position> ASTCustomTypeNode::getEndPosition() {
    return _lexeme->getEndPosition();
}

ASTNodeType ASTCustomTypeNode::getNodeType() {
    return AST_CUSTOM_TYPE_NODE;
}

std::string ASTCustomTypeNode::toString() {
    return "CUSTOM_TYPE";
}

bool ASTCustomTypeNode::isSameAs(std::shared_ptr<ASTNode> other) {
    if (!other->is(this->getNodeType())){
        return false;
    }
    auto otherNode = std::dynamic_pointer_cast<ASTCustomTypeNode>(other);
    return this->getLexeme()->hasSameSymbolTypeAs(otherNode->getLexeme());
}

void ASTCustomTypeNode::print() {
    Logger::log(this->toString(), "-", _lexeme->toString());
}

std::string ASTCustomTypeNode::toSourceCode() {
    return _id;
}