//
// Created by Johny Georges on 2024-05-09.
//

#include "tuple-type-type-signature-strategy.h"
#include "../../../../../../../type-signature/tuple-type-signature/tuple-type-signature.h"

TypeSignature* TupleTypeTypeSignatureStrategy::create(ASTTupleTypeNode* node, TypeSignatureStrategyProvider* strategyMap) {
    auto typeSignatures = new std::vector<TypeSignature*>();
    for (auto type : node->getParameterList()->getParameters()) {
        typeSignatures->push_back(strategyMap->getTypeSignatureForType(type));
    }
    return new TupleTypeSignature(typeSignatures);
}