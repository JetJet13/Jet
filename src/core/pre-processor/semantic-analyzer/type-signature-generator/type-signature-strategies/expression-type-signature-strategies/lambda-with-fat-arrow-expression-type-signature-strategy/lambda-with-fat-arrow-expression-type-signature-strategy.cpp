// Copyright 2026 Johny Georges
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

//
// Created by Johny Georges on 2024-06-07.
//

#include "lambda-with-fat-arrow-expression-type-signature-strategy.h"

void LambdaWithFatArrowExpressionTypeSignatureStrategy::assign(std::shared_ptr<ASTLambdaWithFatArrowExpressionNode> lambdaWithFatArrowExpression, std::shared_ptr<TypeSignatureContext> context, std::shared_ptr<TypeSignatureLookupTable> typeSignatureLookupTable, TypeSignatureStrategyProvider* strategyMap) {
    auto scope = std::make_shared<TypeSignatureLookupTable>(typeSignatureLookupTable);
    scope->inheritGlobalScope(typeSignatureLookupTable);
    for (auto parameter : lambdaWithFatArrowExpression->getParameters()->getParameters()) {
        strategyMap->assignTypeSignatureFor(parameter, context, scope);
        scope->insert(parameter->getParameterTypeSignature()->getName(), parameter->getParameterTypeSignature()->getTypeSignature());
    }

    strategyMap->assignTypeSignatureFor(lambdaWithFatArrowExpression->getParameters(), context, scope);
    strategyMap->assignTypeSignatureFor(lambdaWithFatArrowExpression->getReturnExpression(), context, scope);

    auto returnType = std::optional<std::shared_ptr<TypeSignature>>();
    if (lambdaWithFatArrowExpression->getReturnType()) {
        strategyMap->assignTypeSignatureFor(lambdaWithFatArrowExpression->getReturnType().value(), context, scope);
        returnType = lambdaWithFatArrowExpression->getReturnType().value()->getTypeSignature()->convertToVariableTypeSignature();
    } else {
        returnType = lambdaWithFatArrowExpression->getReturnExpression()->getTypeSignature()->convertToVariableTypeSignature();
    }

    lambdaWithFatArrowExpression->setTypeSignature(std::make_shared<LambdaExpressionTypeSignature>(
            lambdaWithFatArrowExpression->getParameters()->getParameterListTypeSignature(),
            strategyMap->generateLambdaExpressionScopeParameter(lambdaWithFatArrowExpression->getCapturedVariableIds()),
            returnType
    ));
}