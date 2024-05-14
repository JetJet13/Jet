//
// Created by Johny Georges on 2024-05-11.
//

#include "tuple-expression-type-signature-strategy.h"
#include "../../../../../../type-signature/tuple-type-signature/tuple-type-signature.h"

TypeSignature* TupleExpressionTypeSignatureStrategy::create(ASTTupleExpressionNode* node, TypeSignatureStrategyProvider* strategyMap) {
    auto typeSignatures = new std::vector<TypeSignature*>();
    for (auto tupleItem : node->getTupleList()->getItems()) {
        typeSignatures->push_back(strategyMap->getTypeSignatureForExpression(tupleItem->getItem()));
    }
    return new TupleTypeSignature(typeSignatures);
}