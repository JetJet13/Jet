//
// Created by Johny Georges on 2024-05-08.
//

#include "curry-expression-type-signature-strategy.h"
#include "../../../../../../type-signature/invalid-type-signature/invalid-type-signature.h"
#include "../../../../../../type-signature/function-type-signature/function-type-signature.h"

void CurryExpressionTypeSignatureStrategy::assign(ASTCurryExpressionNode* curryExpression, TypeSignatureLookupTable* scope, TypeSignatureStrategyProvider* strategyMap) {
    strategyMap->assignTypeSignatureForExpression(curryExpression->getCallableExpression(), scope);
    if (curryExpression->getCallableExpression()->getTypeSignature()->is(FUNCTION_TYPE_SOURCE)) {
        auto functionTypeSignature = (FunctionTypeSignature*)curryExpression->getCallableExpression()->getTypeSignature();
        curryExpression->setTypeSignature(functionTypeSignature->getReturnType());
        return;
    }

    if (curryExpression->getCallableExpression()->getTypeSignature()->is(CLASS_METHOD_TYPE_SOURCE)) {
        auto classMethod = (FunctionTypeSignature*)curryExpression->getCallableExpression()->getTypeSignature();
        if (classMethod->getReturnType()->isVoid()) {
            curryExpression->setTypeSignature(new InvalidTypeSignature());
            return;
        }
        curryExpression->setTypeSignature(classMethod->getReturnType());
        return;
    }

    curryExpression->setTypeSignature(new InvalidTypeSignature());
}