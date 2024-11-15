//
// Created by Johny Georges on 2024-11-11.
//

#include "lambda-expression-scope-parameter-type-signature-strategy.h"
#include "../../../../../../shared/utils/logger/logger.h"

ParameterListItemTypeSignature* LambdaExpressionScopeParameterTypeSignatureStrategy::create(TypeSignatureLookupTable* scope) {
    auto scopeParameterTypeSignature = new StructTypeSignature();
    for (auto keyValue : scope->getLookupTable()) {
        // we don't want to inject functions into the scope parameter since functions are global
        if (!keyValue.second->isOneOf({ LAMBDA_EXPRESSION_TYPE_SOURCE, FUNCTION_TYPE_SOURCE, PROCEDURE_TYPE_SOURCE, MODULE_TYPE_SOURCE })) {
            scopeParameterTypeSignature->addKeyValuePair(keyValue.first, keyValue.second);
        }
    }
    return new ParameterListItemTypeSignature("scope", scopeParameterTypeSignature);
}