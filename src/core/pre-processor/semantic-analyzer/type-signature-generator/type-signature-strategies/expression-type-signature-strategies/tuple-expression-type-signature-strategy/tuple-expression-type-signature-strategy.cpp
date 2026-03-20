//
// Created by Johny Georges on 2024-05-11.
//

#include "tuple-expression-type-signature-strategy.h"
#include "../../../../../../../shared/utils/logger/logger.h"

void TupleExpressionTypeSignatureStrategy::assign(ASTTupleExpressionNode* node, TypeSignatureContext* context, TypeSignatureLookupTable* scope, TypeSignatureStrategyProvider* strategyMap) {
    auto typeSignatures = new std::vector<TypeSignature*>();
    for (unsigned long i = 0; i < node->numItems(); ++i) {
        auto tupleItem = node->getItems()->at(i);
        strategyMap->assignTypeSignatureFor(tupleItem->getItem(), context, scope);
        auto valueTypeSignature = tupleItem->getItem()->getTypeSignature()->convertToVariableTypeSignature();
        valueTypeSignature->setKeyId(std::to_string(i));
        typeSignatures->push_back(valueTypeSignature);
    }
    node->setTypeSignature(new TupleTypeSignature(typeSignatures));
}