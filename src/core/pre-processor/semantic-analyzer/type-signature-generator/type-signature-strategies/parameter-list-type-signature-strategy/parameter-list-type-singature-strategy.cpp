//
// Created by Johny Georges on 2024-05-04.
//

#include "parameter-list-type-singature-strategy.h"
#include "../../../../../type-signature/parameter-list-type-signature/parameter-list-type-signature.h"

ParameterListTypeSignature* ParameterListTypeSignatureStrategy::create(ASTFunctionParameterListNode* node, TypeSignatureLookupTable* scope, TypeSignatureStrategyProvider* strategyMap) {
    auto parameters = std::vector<ParameterListItemTypeSignature*>();

    for (auto parameterItem : node->getParameters()) {
        parameters.push_back(strategyMap->getTypeSignatureForParameter(parameterItem, scope));
    }

    return new ParameterListTypeSignature(parameters);
}