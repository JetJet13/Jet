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
// Created by Johny Georges on 2024-05-06.
//

#ifndef JETLANG_BINARY_EXPRESSION_TYPE_SIGNATURE_STRATEGY_H
#define JETLANG_BINARY_EXPRESSION_TYPE_SIGNATURE_STRATEGY_H

#include "../../../../../../type-signature/type-signature.h"
#include "../../../../../../ast/ast-nodes/ast-expression-nodes/ast-binary-arithmetic-expression-node.h"
#include "../../type-signature-strategy-provider.h"
#include "types/binary-expression-type-combination.h"
#include "../../../../../../ast/ast-nodes/ast-expression-nodes/ast-binary-comparator-expression-node.h"

class BinaryExpressionTypeSignatureStrategy {
private:
    std::vector<std::shared_ptr<BinaryExpressionTypeCombination>> _arithmeticCombinations;
    std::vector<std::shared_ptr<BinaryExpressionTypeCombination>> _comparatorCombinations;
    void initCombinations();
    std::optional<std::shared_ptr<BinaryExpressionTypeCombination>> findCombination(std::shared_ptr<ASTBinaryArithmeticOperatorNode> binaryOperatorNode);
    std::optional<std::shared_ptr<BinaryExpressionTypeCombination>> findCombination(std::shared_ptr<ASTBinaryComparatorOperatorNode> binaryOperatorNode);
public:
    BinaryExpressionTypeSignatureStrategy();
    void assign(std::shared_ptr<ASTBinaryArithmeticExpressionNode> binaryExpression, std::shared_ptr<TypeSignatureContext> context, std::shared_ptr<TypeSignatureLookupTable> scope, TypeSignatureStrategyProvider* strategyMap);
    void assign(std::shared_ptr<ASTBinaryComparatorExpressionNode> binaryExpression, std::shared_ptr<TypeSignatureContext> context, std::shared_ptr<TypeSignatureLookupTable> scope, TypeSignatureStrategyProvider* strategyMap);
};

#endif //JETLANG_BINARY_EXPRESSION_TYPE_SIGNATURE_STRATEGY_H
