//
// Created by Johny Georges on 2024-05-04.
//

#include "parameter-list-type-singature-strategy.h"

void ParameterListTypeSignatureStrategy::assign(ASTFunctionParameterListNode* node, std::shared_ptr<TypeSignatureContext> context, std::shared_ptr<TypeSignatureLookupTable> scope, TypeSignatureStrategyProvider* strategyMap) {
    auto parameters = std::vector<ParameterListItemTypeSignature*>();

    for (auto parameterItem : node->getParameters()) {
        strategyMap->assignTypeSignatureFor(parameterItem, context, scope);
        parameters.push_back(parameterItem->getTypeSignature());
    }

    node->setTypeSignature(new ParameterListTypeSignature(parameters));
}