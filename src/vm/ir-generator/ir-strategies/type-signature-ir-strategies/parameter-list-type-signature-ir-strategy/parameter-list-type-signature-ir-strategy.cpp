//
// Created by Johny Georges on 2024-07-12.
//

#include "parameter-list-type-signature-ir-strategy.h"

std::shared_ptr<IRParameterListType> ParameterListTypeSignatureIRStrategy::generate(std::shared_ptr<ParameterListTypeSignature> parameterListTypeSignature,  IRGenerator* irGenerator, std::shared_ptr<IRLookupTable> scope, IRContext* irContext, std::optional<std::shared_ptr<ParameterListItemTypeSignature>> scopeParameter) {
    auto parameters = std::vector<std::shared_ptr<IRParameterType>>();
    for (auto parameter : *parameterListTypeSignature->getParameters()) {
        parameters.push_back(irGenerator->generateParameterType(parameter, scope, irContext));
    }

    if (scopeParameter) {
        parameters.push_back(irGenerator->generateParameterType(scopeParameter.value(), scope, irContext));
    }

    return std::make_shared<IRParameterListType>(parameters);
}