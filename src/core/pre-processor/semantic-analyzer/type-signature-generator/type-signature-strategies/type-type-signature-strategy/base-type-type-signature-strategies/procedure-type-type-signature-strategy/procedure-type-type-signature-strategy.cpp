//
// Created by Johny Georges on 2024-06-08.
//

#include "procedure-type-type-signature-strategy.h"
#include "../../../../../../../type-signature/invocable-type-signature/lambda-type-signature/procedure-lambda-type-signature/procedure-lambda-type-signature.h"


void ProcedureTypeTypeSignatureStrategy::assign(ASTProcedureTypeNode* node, TypeSignatureLookupTable* scope, TypeSignatureStrategyProvider* strategyMap) {
    auto typeSignatures = new std::vector<TypeSignature*>();
    for (auto type : node->getParameterList()->getParameters()) {
        strategyMap->assignTypeSignatureFor(type, scope);
        typeSignatures->push_back(type->getTypeSignature());
    }

    node->setTypeSignature(new ProcedureLambdaTypeSignature(typeSignatures));
}