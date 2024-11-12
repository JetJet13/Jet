//
// Created by Johny Georges on 2024-11-11.
//

#include "lambda-expression-scope-parameter-type-signature-strategy.h"

StructTypeSignature* LambdaExpressionScopeParameterTypeSignatureStrategy::create(TypeSignatureLookupTable* scope) {
    auto scopeParameterTypeSignature = new StructTypeSignature();
    for (auto keyValue : scope->getLookupTable()) {
        scopeParameterTypeSignature->addKeyValuePair(keyValue.first, keyValue.second);
    }
    return scopeParameterTypeSignature;
}