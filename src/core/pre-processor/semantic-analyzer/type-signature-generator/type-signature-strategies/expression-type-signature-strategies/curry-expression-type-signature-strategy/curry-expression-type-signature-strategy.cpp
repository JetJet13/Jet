//
// Created by Johny Georges on 2024-05-08.
//

#include "curry-expression-type-signature-strategy.h"
#include "../../../../../../type-signature/invalid-type-signature/invalid-type-signature.h"
#include "../../../../../../../shared/utils/logger/logger.h"
#include "../../../../../../type-signature/invocable-type-signature/function-type-signature/function-invocation-type-signature/function-invocation-type-signature.h"

void CurryExpressionTypeSignatureStrategy::assign(ASTCurryExpressionNode* curryExpression, TypeSignatureContext* context, TypeSignatureLookupTable* scope, TypeSignatureStrategyProvider* strategyMap) {
    strategyMap->assignTypeSignatureFor(curryExpression->getCallableExpression(), context, scope);
    for (auto argument : *curryExpression->getArguments()->getArguments()) {
        strategyMap->assignTypeSignatureFor(argument->getArgument(), context);
    }

    if (curryExpression->getCallableExpression()->getTypeSignature()->typeSourceIs(FUNCTION_INVOCATION_TYPE_SOURCE)) {
        auto functionInvocationTypeSignature = (FunctionInvocationTypeSignature*)curryExpression->getCallableExpression()->getTypeSignature();
        curryExpression->setTypeSignature(functionInvocationTypeSignature->getReturnType()->getTargetTypeSignature());
        return;
    }

    curryExpression->setTypeSignature(new InvalidTypeSignature());
}