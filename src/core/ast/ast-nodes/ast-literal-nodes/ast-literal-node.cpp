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
// Created by Johny Georges on 2024-02-17.
//

#include "ast-literal-node.h"

ASTLiteralNode::ASTLiteralNode(std::shared_ptr<Lexeme> lexemeLiteral) {
    _lexeme = lexemeLiteral;
}

std::shared_ptr<Lexeme> ASTLiteralNode::getLiteral() {
    return _lexeme;
}

void ASTLiteralNode::setTypeSignature(std::shared_ptr<LiteralTypeSignature> typeSignature) {
    _typeSignature = typeSignature;
}

std::shared_ptr<LiteralTypeSignature> ASTLiteralNode::getLiteralTypeSignature() {
    return std::dynamic_pointer_cast<LiteralTypeSignature>(_typeSignature);
}

std::shared_ptr<TypeSignature> ASTLiteralNode::getTypeSignature() {
    return _typeSignature;
}

std::shared_ptr<Position> ASTLiteralNode::getStartPosition() {
    return _lexeme->getStartPosition();
}

std::shared_ptr<Position> ASTLiteralNode::getEndPosition() {
    return _lexeme->getEndPosition();
}

ASTNodeType ASTLiteralNode::getNodeType() {
    return AST_LITERAL_NODE;
}

std::string ASTLiteralNode::toString() {
    return "LITERAL";
}


bool ASTLiteralNode::isSameAs(std::shared_ptr<ASTNode> other) {
    if (!other->is(this->getNodeType())) {
        return false;
    }
    auto otherNode = std::dynamic_pointer_cast<ASTLiteralNode>(other);
    return this->getLiteral()->hasSameSymbolTypeAs(otherNode->getLiteral());
}

std::string ASTLiteralNode::toSourceCode() {
    return _lexeme->getToken()->getRawValue();
}