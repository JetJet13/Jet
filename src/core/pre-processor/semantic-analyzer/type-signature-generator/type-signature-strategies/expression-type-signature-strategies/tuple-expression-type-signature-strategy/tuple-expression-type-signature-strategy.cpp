//
// Created by Johny Georges on 2024-05-11.
//

#include "tuple-expression-type-signature-strategy.h"
#include "../../../../../../type-signature/tuple-type-signature/tuple-type-signature.h"
#include "../../../../../../../shared/utils/logger/logger.h"

void TupleExpressionTypeSignatureStrategy::assign(ASTTupleExpressionNode* node, TypeSignatureLookupTable* scope, TypeSignatureStrategyProvider* strategyMap) {
    auto typeSignatures = new std::vector<TypeSignature*>();
    for (auto tupleItem : node->getTupleList()->getItems()) {
        Logger::log("tuple item", tupleItem->getItem()->toString());
        strategyMap->assignTypeSignatureFor(tupleItem->getItem(), scope);
        Logger::log("pushed");
        typeSignatures->push_back(tupleItem->getItem()->getTypeSignature());
    }
    node->setTypeSignature(new TupleTypeSignature(typeSignatures));
}