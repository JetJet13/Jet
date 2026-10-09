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
// Created by Johny Georges on 2024-03-26.
//

#include "ast-tuple-access-node.h"
#include "../../../../shared/utils/logger/logger.h"

ASTTupleAccessNode::ASTTupleAccessNode(std::shared_ptr<Lexeme> lexeme) {
    _lexeme = lexeme;
}

std::shared_ptr<Lexeme> ASTTupleAccessNode::getLexeme() {
    return _lexeme;
}

std::shared_ptr<Position> ASTTupleAccessNode::getStartPosition() {
    return _lexeme->getStartPosition();
}

std::shared_ptr<Position> ASTTupleAccessNode::getEndPosition() {
    return _lexeme->getEndPosition();
}

ASTNodeType ASTTupleAccessNode::getNodeType() {
    return AST_TUPLE_ACCESS_NODE;
}

std::string ASTTupleAccessNode::toString() {
    return "TUPLE_ACCESS";
}

bool ASTTupleAccessNode::isSameAs(std::shared_ptr<ASTNode> other) {
    if (!other->is(this->getNodeType())){
        return false;
    }
    auto otherNode = std::dynamic_pointer_cast<ASTTupleAccessNode>(other);
    return this->getLexeme()->hasSameSymbolTypeAs(otherNode->getLexeme());
}

void ASTTupleAccessNode::print() {
    Logger::log(this->toString(), "-", _lexeme->toString());
}

std::string ASTTupleAccessNode::toSourceCode() {
    return _lexeme->getToken()->getRawValue();
}

std::shared_ptr<ASTTupleAccessNode> ASTTupleAccessNode::setIndexValue(std::string index) {
    _index = std::stoll(index);
    return std::dynamic_pointer_cast<ASTTupleAccessNode>(shared_from_this());
}

int64_t ASTTupleAccessNode::getIndexValue() {
    return _index;
}