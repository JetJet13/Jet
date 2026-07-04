//
// Created by Johny Georges on 2024-12-09.
//

#include "class-scope-parameter-type-signature-strategy.h"

std::shared_ptr<ParameterListItemTypeSignature> ClassScopeParameterTypeSignatureStrategy::create(std::shared_ptr<ClassTypeSignature> classTypeSignature) {
    auto scopeParameterTypeSignature = std::make_shared<StructTypeSignature>();
    for (const auto& keyValue : classTypeSignature->getInstanceProperties()->getKeyValues()) {
        auto typeSignature = keyValue.second->getType()->convertToVariableTypeSignature();
        scopeParameterTypeSignature->addKeyValuePair(classTypeSignature->stripClassNameFromKey(keyValue.first), typeSignature);
    }
    return ParameterListItemTypeSignature::createClassScopeParameter(std::make_shared<PointerTypeSignature>(scopeParameterTypeSignature));
}