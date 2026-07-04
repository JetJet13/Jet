//
// Created by Johny Georges on 2024-05-09.
//

#include "tuple-type-type-signature-strategy.h"
#include "../../../../../../../type-signature/tuple-type-signature/tuple-type-signature.h"

void TupleTypeTypeSignatureStrategy::assign(std::shared_ptr<ASTTupleTypeNode> node, std::shared_ptr<TypeSignatureContext> context, std::shared_ptr<TypeSignatureLookupTable> scope, TypeSignatureStrategyProvider* strategyMap) {
    auto typeSignatures = new std::vector<std::shared_ptr<TypeSignature>>();
    for (auto type : node->getValueTypes()) {
        strategyMap->assignTypeSignatureFor(type, context, scope);
        typeSignatures->push_back(type->getTypeSignature());
    }
    node->setTypeSignature(std::make_shared<TupleTypeSignature>(typeSignatures));
}