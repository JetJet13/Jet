//
// Created by Johny Georges on 2024-05-11.
//

#include "tuple-expression-type-signature-strategy.h"
#include "../../../../../../type-signature/tuple-type-signature/tuple-type-signature.h"

void TupleExpressionTypeSignatureStrategy::assign(ASTTupleExpressionNode* node, TypeSignatureLookupTable* scope, TypeSignatureStrategyProvider* strategyMap) {
    auto typeSignatures = new std::vector<TypeSignature*>();
    for (auto tupleItem : node->getTupleList()->getItems()) {
        strategyMap->assignTypeSignatureForExpression(tupleItem->getItem(), scope);
        typeSignatures->push_back(tupleItem->getItem()->getTypeSignature());
    }
    node->setTypeSignature(new TupleTypeSignature(typeSignatures));
}