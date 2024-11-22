//
// Created by Johny Georges on 2024-07-12.
//

#include "parameter-list-type-signature-ir-strategy.h"

IRParameterListType* ParameterListTypeSignatureIRStrategy::generate(ParameterListTypeSignature* parameterListTypeSignature, std::unique_ptr<llvm::LLVMContext>* context, IRGenerator* irGenerator, std::optional<ParameterListItemTypeSignature*> scopeParameter) {
    auto parameters = std::vector<IRParameterType*>();
    if (scopeParameter) {
        parameters.push_back(irGenerator->generateParameterType(scopeParameter.value()));
    }
    for (auto parameter : *parameterListTypeSignature->getParameters()) {
        parameters.push_back(irGenerator->generateParameterType(parameter));
    }

    return new IRParameterListType(parameters);
}