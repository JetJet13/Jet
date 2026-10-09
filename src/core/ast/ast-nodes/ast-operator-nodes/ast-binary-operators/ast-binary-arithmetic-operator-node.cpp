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
// Created by Johny Georges on 2024-02-07.
//

#include "ast-binary-arithmetic-operator-node.h"
#include "../../../../../shared/utils/logger/logger.h"

ASTBinaryArithmeticOperatorNode::ASTBinaryArithmeticOperatorNode(std::shared_ptr<Lexeme> lexeme) {
    _lexeme = lexeme;
    _priority = this->determinePriority(lexeme);
}

std::shared_ptr<Lexeme> ASTBinaryArithmeticOperatorNode::getOperator() {
    return _lexeme;
}

unsigned int ASTBinaryArithmeticOperatorNode::getPriority() const {
    return _priority;
}

bool ASTBinaryArithmeticOperatorNode::isHigherOrEqualPriorityThan(std::shared_ptr<ASTBinaryArithmeticOperatorNode> other) const {
    return _priority <= other->getPriority();
}

bool ASTBinaryArithmeticOperatorNode::isPlus() {
    return _lexeme->getToken()->getSymbol()->isPlus();
}

bool ASTBinaryArithmeticOperatorNode::isMinus() {
    return _lexeme->getToken()->getSymbol()->isMinus();
}

bool ASTBinaryArithmeticOperatorNode::isMultiply() {
    return _lexeme->getToken()->getSymbol()->isStar();
}

bool ASTBinaryArithmeticOperatorNode::isDivide() {
    return _lexeme->getToken()->getSymbol()->isSlash();
}

bool ASTBinaryArithmeticOperatorNode::isModulo() {
    return _lexeme->getToken()->getSymbol()->isModulo();
}

std::shared_ptr<Position> ASTBinaryArithmeticOperatorNode::getStartPosition() {
    return _lexeme->getStartPosition();
}

std::shared_ptr<Position> ASTBinaryArithmeticOperatorNode::getEndPosition() {
    return _lexeme->getEndPosition();
}

ASTNodeType ASTBinaryArithmeticOperatorNode::getNodeType() {
    return AST_BINARY_ARITHMETIC_OPERATOR_NODE;
}

std::string ASTBinaryArithmeticOperatorNode::toString() {
    return "BINARY_ARITHMETIC_OPERATOR";
}

bool ASTBinaryArithmeticOperatorNode::isSameAs(std::shared_ptr<ASTNode> other) {
    if (!other->is(this->getNodeType())){
        return false;
    }
    auto otherNode = std::dynamic_pointer_cast<ASTBinaryArithmeticOperatorNode>(other);
    return this->getOperator()->hasSameSymbolTypeAs(otherNode->getOperator());
}

void ASTBinaryArithmeticOperatorNode::print() {
    Logger::log(this->toString(), "-", _lexeme->toString(), "|", "id:", _id);
}

std::string ASTBinaryArithmeticOperatorNode::toSourceCode() {
    return this->getOperator()->getToken()->getSymbol()->toString();
}

unsigned int ASTBinaryArithmeticOperatorNode::determinePriority(std::shared_ptr<Lexeme> lexeme) {
    auto symbol = lexeme->getToken()->getSymbol();
    if (symbol->isSlash() || symbol->isStar()) {
        return 1;
    } else if (symbol->isMinus() || symbol->isPlus()) {
        return 2;
    } else {
        return 10;
    }
}