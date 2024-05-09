//
// Created by Johny Georges on 2024-05-06.
//

#ifndef JETLANG_BINARY_EXPRESSION_TYPE_SIGNATURE_STRATEGY_H
#define JETLANG_BINARY_EXPRESSION_TYPE_SIGNATURE_STRATEGY_H

#include "../../../../../../type-signature/type-signature.h"
#include "../../../../../../ast/ast-nodes/ast-expression-nodes/ast-binary-expression-node.h"
#include "../../type-signature-strategy-provider.h"
#include "types/binary-expression-type-combination.h"

class BinaryExpressionTypeSignatureStrategy {
private:
    std::vector<BinaryExpressionTypeCombination*> _combinations;
    void initCombinations();
    std::optional<BinaryExpressionTypeCombination*> findCombination(ASTBinaryOperatorNode* binaryOperatorNode);
public:
    BinaryExpressionTypeSignatureStrategy();
    TypeSignature* create(ASTBinaryExpressionNode* binaryExpression, TypeSignatureStrategyProvider* strategyMap);
};

#endif //JETLANG_BINARY_EXPRESSION_TYPE_SIGNATURE_STRATEGY_H
