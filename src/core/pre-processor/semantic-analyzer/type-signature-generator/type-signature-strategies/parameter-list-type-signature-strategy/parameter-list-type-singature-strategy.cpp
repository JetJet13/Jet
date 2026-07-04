//
// Created by Johny Georges on 2024-05-04.
//

#include "parameter-list-type-singature-strategy.h"

void ParameterListTypeSignatureStrategy::assign(std::shared_ptr<ASTFunctionParameterListNode> node, std::shared_ptr<TypeSignatureContext> context, std::shared_ptr<TypeSignatureLookupTable> scope, TypeSignatureStrategyProvider* strategyMap) {
    auto parameters = std::vector<std::shared_ptr<ParameterListItemTypeSignature>>();

    for (auto parameterItem : node->getParameters()) {
        strategyMap->assignTypeSignatureFor(parameterItem, context, scope);
        parameters.push_back(parameterItem->getParameterTypeSignature());
    }

    node->setTypeSignature(std::make_shared<ParameterListTypeSignature>(parameters));
}