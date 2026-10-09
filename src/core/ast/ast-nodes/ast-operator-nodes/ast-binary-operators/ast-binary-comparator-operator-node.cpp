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
// Created by Johny Georges on 2026-03-02.
//

#include "ast-binary-comparator-operator-node.h"
#include "../../../../../shared/utils/logger/logger.h"

ASTBinaryComparatorOperatorNode::ASTBinaryComparatorOperatorNode(std::shared_ptr<Lexeme> lexeme) {
    _lexeme = lexeme;
}

std::shared_ptr<Lexeme> ASTBinaryComparatorOperatorNode::getOperator() {
    return _lexeme;
}

bool ASTBinaryComparatorOperatorNode::isEqual() {
    return _lexeme->getToken()->getSymbol()->isEqualityOperator();
}

bool ASTBinaryComparatorOperatorNode::isNotEqual() {
    return _lexeme->getToken()->getSymbol()->isInequalityOperator();
}

bool ASTBinaryComparatorOperatorNode::isGreaterThan() {
    return _lexeme->getToken()->getSymbol()->isGreaterThan();
}

bool ASTBinaryComparatorOperatorNode::isLessThan() {
    return _lexeme->getToken()->getSymbol()->isLessThan();
}

bool ASTBinaryComparatorOperatorNode::isGreaterThanOrEqual() {
    return _lexeme->getToken()->getSymbol()->isGreaterThanOrEqual();
}

bool ASTBinaryComparatorOperatorNode::isLessThanOrEqual() {
    return _lexeme->getToken()->getSymbol()->isLessThanOrEqual();
}

std::shared_ptr<Position> ASTBinaryComparatorOperatorNode::getStartPosition() {
    return _lexeme->getStartPosition();
}

std::shared_ptr<Position> ASTBinaryComparatorOperatorNode::getEndPosition() {
    return _lexeme->getEndPosition();
}

ASTNodeType ASTBinaryComparatorOperatorNode::getNodeType() {
    return AST_BINARY_COMPARATOR_OPERATOR_NODE;
}

std::string ASTBinaryComparatorOperatorNode::toString() {
    return "BINARY_COMPARATOR_OPERATOR";
}

bool ASTBinaryComparatorOperatorNode::isSameAs(std::shared_ptr<ASTNode> other) {
    if (!other->is(this->getNodeType())){
        return false;
    }
    auto otherNode = std::dynamic_pointer_cast<ASTBinaryComparatorOperatorNode>(other);
    return this->getOperator()->hasSameSymbolTypeAs(otherNode->getOperator());
}

void ASTBinaryComparatorOperatorNode::print() {
    Logger::log(this->toString(), "-", _lexeme->toString(), "|", "id:", _id);
}

std::string ASTBinaryComparatorOperatorNode::toSourceCode() {
    return this->getOperator()->getToken()->getSymbol()->toString();
}