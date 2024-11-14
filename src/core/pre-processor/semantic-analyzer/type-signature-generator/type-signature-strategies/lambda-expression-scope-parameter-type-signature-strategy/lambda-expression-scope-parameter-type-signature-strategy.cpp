//
// Created by Johny Georges on 2024-11-11.
//

#include "lambda-expression-scope-parameter-type-signature-strategy.h"

ParameterListItemTypeSignature* LambdaExpressionScopeParameterTypeSignatureStrategy::create(TypeSignatureLookupTable* scope) {
    auto scopeParameterTypeSignature = new StructTypeSignature();
    for (auto keyValue : scope->getLookupTable()) {
        scopeParameterTypeSignature->addKeyValuePair(keyValue.first, keyValue.second);
    }
    return new ParameterListItemTypeSignature("scope", scopeParameterTypeSignature);
}