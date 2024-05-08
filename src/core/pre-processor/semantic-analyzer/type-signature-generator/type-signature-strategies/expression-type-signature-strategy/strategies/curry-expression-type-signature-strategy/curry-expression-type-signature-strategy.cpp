//
// Created by Johny Georges on 2024-05-08.
//

#include "curry-expression-type-signature-strategy.h"
#include "../../../../../../../type-signature/invalid-type-signature/invalid-type-signature.h"
#include "../../../../../../../type-signature/function-type-signature/function-type-signature.h"

TypeSignature* CurryExpressionTypeSignatureStrategy::create(ASTCurryExpressionNode* curryExpression, ExpressionTypeSignatureStrategyProvider* strategyMap) {
    auto callableExpressionTypeSignature = strategyMap->getTypeSignatureForExpression(curryExpression->getCallableExpression());
    if (callableExpressionTypeSignature->hasTypeSource(FUNCTION_TYPE_SOURCE)) {
        auto functionTypeSignature = (FunctionTypeSignature*)callableExpressionTypeSignature;
        return functionTypeSignature->getReturnType();
    }

    if (callableExpressionTypeSignature->hasTypeSource(CLASS_METHOD_TYPE_SOURCE)) {
        auto classMethod = (FunctionTypeSignature*)callableExpressionTypeSignature;
        if (classMethod->getReturnType()->isVoid()) {
            return new InvalidTypeSignature();
        }
        return classMethod->getReturnType();
    }

    return new InvalidTypeSignature();
}