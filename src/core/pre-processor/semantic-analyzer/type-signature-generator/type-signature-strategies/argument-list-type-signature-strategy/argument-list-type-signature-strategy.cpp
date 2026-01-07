//
// Created by Johny Georges on 2024-12-31.
//

#include "argument-list-type-signature-strategy.h"

void ArgumentListTypeSignatureStrategy::assign(ASTFunctionArgumentListNode* node, TypeSignatureLookupTable* scope, TypeSignatureStrategyProvider* strategyMap) {
    auto argumentTypes = std::vector<TypeSignature*>();

    for (auto argument : *node->getArguments()) {
        strategyMap->assignTypeSignatureFor(argument->getArgument(), scope);
        argumentTypes.push_back(argument->getArgument()->getTypeSignature()->convertToVariableTypeSignature());
    }

    node->setTypeSignature(new ArgumentListTypeSignature(argumentTypes));
}