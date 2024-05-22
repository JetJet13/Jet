//
// Created by Johny Georges on 2024-05-11.
//

#include "tuple-access-expression-type-signature-strategy.h"
#include "../../../../../../type-signature/invalid-type-signature/invalid-type-signature.h"
#include "../../../../../../type-signature/tuple-type-signature/tuple-type-signature.h"

void TupleAccessExpressionTypeSignatureStrategy::assign(ASTTupleAccessExpressionNode* tupleAccessExpression, TypeSignatureLookupTable* scope, TypeSignatureStrategyProvider* strategyMap) {
    strategyMap->assignTypeSignatureForExpression(tupleAccessExpression->getSource()->getSource(), scope);
    if (!tupleAccessExpression->getSource()->getSource()->getTypeSignature()->is(TUPLE_TYPE_SOURCE)) {
        tupleAccessExpression->setTypeSignature(new InvalidTypeSignature());
        return;
    }

    auto tupleTypeSignature = (TupleTypeSignature*)tupleAccessExpression->getSource()->getSource()->getTypeSignature();
    tupleAccessExpression->setTypeSignature(tupleTypeSignature->getTypeSignatureAtIndex(tupleAccessExpression->getIndex()->getIndexValue()));
}