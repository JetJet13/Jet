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
