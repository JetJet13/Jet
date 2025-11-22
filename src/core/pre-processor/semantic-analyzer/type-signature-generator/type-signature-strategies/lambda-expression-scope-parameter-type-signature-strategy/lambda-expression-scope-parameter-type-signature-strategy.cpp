//
// Created by Johny Georges on 2024-11-11.
//

#include "lambda-expression-scope-parameter-type-signature-strategy.h"
#include "../../../../../../shared/utils/logger/logger.h"

ParameterListItemTypeSignature* LambdaExpressionScopeParameterTypeSignatureStrategy::create(std::vector<std::string>* captureVariableIds) {
    return ParameterListItemTypeSignature::createScopeParameter(new LambdaScopeTypeSignature(captureVariableIds));
}