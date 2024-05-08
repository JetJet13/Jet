//
// Created by Johny Georges on 2024-05-07.
//

#ifndef JETLANG_ARRAY_ACCESS_EXPRESSION_TYPE_SIGNATURE_STRATEGY_H
#define JETLANG_ARRAY_ACCESS_EXPRESSION_TYPE_SIGNATURE_STRATEGY_H

#include "../../../../../../../ast/ast-nodes/ast-expression-nodes/ast-array-access-expression-node.h"
#include "../../../../../../../type-signature/type-signature.h"
#include "../../expression-type-signature-strategy-provider.h"

class ArrayAccessExpressionTypeSignatureStrategy {
public:
    TypeSignature* create(ASTArrayAccessExpressionNode* arrayAccessExpression, ExpressionTypeSignatureStrategyProvider* strategyMap);
};

#endif //JETLANG_ARRAY_ACCESS_EXPRESSION_TYPE_SIGNATURE_STRATEGY_H
