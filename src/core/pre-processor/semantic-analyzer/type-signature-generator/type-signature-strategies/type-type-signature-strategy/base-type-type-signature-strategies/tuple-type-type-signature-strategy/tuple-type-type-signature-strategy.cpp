//
// Created by Johny Georges on 2024-05-09.
//

#include "tuple-type-type-signature-strategy.h"
#include "../../../../../../../type-signature/tuple-type-signature/tuple-type-signature.h"

void TupleTypeTypeSignatureStrategy::assign(ASTTupleTypeNode* node, TypeSignatureContext* context, TypeSignatureLookupTable* scope, TypeSignatureStrategyProvider* strategyMap) {
    auto typeSignatures = new std::vector<TypeSignature*>();
    for (auto type : node->getValueTypes()) {
        strategyMap->assignTypeSignatureFor(type, context, scope);
        typeSignatures->push_back(type->getTypeSignature());
    }
    node->setTypeSignature(new TupleTypeSignature(typeSignatures));
}