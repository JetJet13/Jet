//
// Created by Johny Georges on 2025-06-18.
//

#include "tuple-access-invocation-expression-type-signature-strategy.h"
#include "../../../../../../type-signature/invalid-type-signature/invalid-type-signature.h"
#include "../../../../../../type-signature/tuple-type-signature/tuple-type-signature.h"

void TupleAccessInvocationExpressionTypeSignatureStrategy::assign(ASTTupleAccessInvocationExpressionNode* tupleAccessInvocationExpression, TypeSignatureContext* context, TypeSignatureLookupTable* scope, TypeSignatureStrategyProvider* strategyMap) {
    strategyMap->assignTypeSignatureFor(tupleAccessInvocationExpression->getSource()->getSource(), context, scope);
    strategyMap->assignTypeSignatureFor(tupleAccessInvocationExpression->getArguments(), context, scope);

    if (tupleAccessInvocationExpression->getSource()->getSource()->getTypeSignature()->typeTargetIs(TUPLE_TYPE_SOURCE)) {
        strategyMap->assignTypeSignatureFor(tupleAccessInvocationExpression->getObjectAccess(), context, scope);
        auto tupleSource = (TupleTypeSignature*)tupleAccessInvocationExpression->getSource()->getSource()->getTypeSignature();
        auto functionTypeSignature = (InvocableTypeSignature*)tupleSource->getTypeSignatureAtIndex(
                tupleAccessInvocationExpression->getIndex()->getIndexValue()
        );
        tupleAccessInvocationExpression->getObjectAccess()->setTypeSignature(functionTypeSignature);
        tupleAccessInvocationExpression->setTypeSignature(functionTypeSignature->getReturnType());
        return;
    }
    tupleAccessInvocationExpression->setTypeSignature(new InvalidTypeSignature());
}