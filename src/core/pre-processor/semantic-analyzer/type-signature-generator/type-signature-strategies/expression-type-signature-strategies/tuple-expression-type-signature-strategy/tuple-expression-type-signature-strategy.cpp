//
// Created by Johny Georges on 2024-05-11.
//

#include "tuple-expression-type-signature-strategy.h"
#include "../../../../../../../shared/utils/logger/logger.h"

void TupleExpressionTypeSignatureStrategy::assign(ASTTupleExpressionNode* node, TypeSignatureLookupTable* scope, TypeSignatureStrategyProvider* strategyMap) {
    auto typeSignatures = new std::vector<TypeSignature*>();
    for (auto tupleItem : node->getItems()) {
        strategyMap->assignTypeSignatureFor(tupleItem->getItem(), scope);
        typeSignatures->push_back(tupleItem->getItem()->getTypeSignature()->convertToVariableTypeSignature());
    }
    node->setTypeSignature(new TupleTypeSignature(typeSignatures));
}