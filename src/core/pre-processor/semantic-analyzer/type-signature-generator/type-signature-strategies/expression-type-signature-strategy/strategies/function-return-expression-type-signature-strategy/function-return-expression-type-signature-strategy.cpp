//
// Created by Johny Georges on 2024-05-08.
//

#include "function-return-expression-type-signature-strategy.h"

TypeSignature* FunctionReturnExpressionTypeSignatureStrategy::create(ASTFunctionReturnExpressionNode* functionReturnExpression, ExpressionTypeSignatureStrategyProvider* strategyMap) {
    return strategyMap->getTypeSignatureForExpression(functionReturnExpression->getExpression());
}