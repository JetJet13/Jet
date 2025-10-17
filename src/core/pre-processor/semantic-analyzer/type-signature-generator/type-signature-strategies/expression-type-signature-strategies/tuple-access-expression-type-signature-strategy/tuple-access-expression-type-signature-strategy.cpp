//
// Created by Johny Georges on 2024-05-11.
//

#include "tuple-access-expression-type-signature-strategy.h"
#include "../../../../../../type-signature/invalid-type-signature/invalid-type-signature.h"
#include "../../../../../../type-signature/tuple-type-signature/tuple-type-signature.h"
#include "../../../../../../type-signature/ref-type-signature/ref-type-signature.h"

void TupleAccessExpressionTypeSignatureStrategy::assign(ASTTupleAccessExpressionNode* tupleAccessExpression, TypeSignatureLookupTable* scope, TypeSignatureStrategyProvider* strategyMap) {
    strategyMap->assignTypeSignatureFor(tupleAccessExpression->getSource()->getSource(), scope);
    auto sourceTypeSignature = tupleAccessExpression->getSource()->getSource()->getTypeSignature();
    if (sourceTypeSignature->typeSourceIs(REF_TYPE_SOURCE)) {
        sourceTypeSignature = ((RefTypeSignature*)sourceTypeSignature)->getUnderlyingType();
    }

    if (sourceTypeSignature->typeTargetIs(TUPLE_TYPE_SOURCE)) {
        auto tupleTypeSignature = (TupleTypeSignature*)sourceTypeSignature;
        tupleAccessExpression->setTypeSignature(tupleTypeSignature->getTypeSignatureAtIndex(tupleAccessExpression->getIndex()->getIndexValue()));
        return;
    }

    tupleAccessExpression->setTypeSignature(new InvalidTypeSignature());
}