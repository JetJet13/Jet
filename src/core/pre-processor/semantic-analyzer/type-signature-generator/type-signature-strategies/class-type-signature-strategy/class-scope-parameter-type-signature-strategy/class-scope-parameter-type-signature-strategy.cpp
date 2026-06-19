//
// Created by Johny Georges on 2024-12-09.
//

#include "class-scope-parameter-type-signature-strategy.h"

ParameterListItemTypeSignature* ClassScopeParameterTypeSignatureStrategy::create(ClassTypeSignature* classTypeSignature) {
    auto scopeParameterTypeSignature = new StructTypeSignature();
    for (const auto& keyValue : classTypeSignature->getInstanceProperties()->getKeyValues()) {
        auto typeSignature = keyValue.second->getType()->convertToVariableTypeSignature();
        typeSignature->setKeyId(classTypeSignature->stripClassNameFromKey(keyValue.first));
        scopeParameterTypeSignature->addKeyValuePair(keyValue.first, typeSignature);
    }
    return ParameterListItemTypeSignature::createClassScopeParameter(new PointerTypeSignature(scopeParameterTypeSignature));
}