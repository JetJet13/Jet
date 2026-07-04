//
// Created by Johny Georges on 2024-11-11.
//

#include "lambda-expression-scope-parameter-type-signature-strategy.h"
#include "../../../../../../shared/utils/logger/logger.h"

std::shared_ptr<ParameterListItemTypeSignature> LambdaExpressionScopeParameterTypeSignatureStrategy::create(std::set<std::string>* captureVariableIds) {
    return ParameterListItemTypeSignature::createScopeParameter(std::make_shared<LambdaScopeTypeSignature>(captureVariableIds));
}