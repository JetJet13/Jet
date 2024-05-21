//
// Created by Johny Georges on 2024-05-11.
//

#include "tuple-access-expression-type-signature-strategy.h"
#include "../../../../../../type-signature/invalid-type-signature/invalid-type-signature.h"
#include "../../../../../../type-signature/tuple-type-signature/tuple-type-signature.h"

TypeSignature* TupleAccessExpressionTypeSignatureStrategy::create(ASTTupleAccessExpressionNode* tupleAccessExpression, TypeSignatureLookupTable* scope, TypeSignatureStrategyProvider* strategyMap) {
    auto sourceTypeSignature = strategyMap->getTypeSignatureForExpression(tupleAccessExpression->getSource()->getSource(), scope);
    if (!sourceTypeSignature->is(TUPLE_TYPE_SOURCE)) {
        return new InvalidTypeSignature();
    }

    auto tupleTypeSignature = (TupleTypeSignature*)sourceTypeSignature;
    return tupleTypeSignature->getTypeSignatureAtIndex(tupleAccessExpression->getIndex()->getIndexValue());
}