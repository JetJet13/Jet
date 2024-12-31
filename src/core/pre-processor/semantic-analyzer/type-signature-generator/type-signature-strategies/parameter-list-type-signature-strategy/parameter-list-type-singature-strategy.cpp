//
// Created by Johny Georges on 2024-05-04.
//

#include "parameter-list-type-singature-strategy.h"

// todo: add function argument list type signature strategy

void ParameterListTypeSignatureStrategy::assign(ASTFunctionParameterListNode* node, TypeSignatureLookupTable* scope, TypeSignatureStrategyProvider* strategyMap) {
    auto parameters = std::vector<ParameterListItemTypeSignature*>();

    for (auto parameterItem : node->getParameters()) {
        strategyMap->assignTypeSignatureFor(parameterItem, scope);
        parameters.push_back(parameterItem->getTypeSignature());
    }

    node->setTypeSignature(new ParameterListTypeSignature(parameters));
}