//
// Created by Johny Georges on 2024-12-09.
//

#include "class-scope-parameter-type-signature-strategy.h"

ParameterListItemTypeSignature* ClassScopeParameterTypeSignatureStrategy::create(ClassTypeSignature* classTypeSignature) {
    auto scopeParameterTypeSignature = new StructTypeSignature();
    for (const auto& keyValue : classTypeSignature->getProperties()->getKeyValues()) {
        scopeParameterTypeSignature->addKeyValuePair(keyValue.first, keyValue.second->getType());
    }
    return ParameterListItemTypeSignature::createClassScopeParameter(new PointerTypeSignature(scopeParameterTypeSignature));
}