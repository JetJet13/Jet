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
// Created by Johny Georges on 2024-05-08.
//

#include "lambda-expression-type-signature-strategy.h"
#include "../../../../../../../shared/utils/logger/logger.h"

void LambdaExpressionTypeSignatureStrategy::assign(std::shared_ptr<ASTLambdaExpressionNode> lambdaExpression, std::shared_ptr<TypeSignatureContext> context, std::shared_ptr<TypeSignatureLookupTable> typeSignatureLookupTable, TypeSignatureStrategyProvider* strategyMap) {
    auto scope = std::make_shared<TypeSignatureLookupTable>(typeSignatureLookupTable);
    scope->inheritGlobalScope(typeSignatureLookupTable);
    for (auto parameter : lambdaExpression->getParameters()->getParameters()) {
        strategyMap->assignTypeSignatureFor(parameter, context, scope);
        scope->insert(parameter->getParameterTypeSignature()->getName(), parameter->getParameterTypeSignature()->getTypeSignature());
    }
    strategyMap->assignTypeSignatureFor(lambdaExpression->getParameters(), context, scope);
    strategyMap->assignTypeSignatureFor(lambdaExpression->getBlock(), context, scope);
    auto returnType = std::optional<std::shared_ptr<TypeSignature>>();
    if (lambdaExpression->getReturnType()) {
        strategyMap->assignTypeSignatureFor(lambdaExpression->getReturnType().value(), context, scope);
        returnType = lambdaExpression->getReturnType().value()->getTypeSignature()->convertToVariableTypeSignature();
    } else {
        for (auto node : *lambdaExpression->getBlock()->getReturnStatements()) {
            if (!returnType) {
                returnType = node->getTypeSignature()->convertToVariableTypeSignature();
            }
        }
    }

    lambdaExpression->setTypeSignature(std::make_shared<LambdaExpressionTypeSignature>(
        lambdaExpression->getParameters()->getParameterListTypeSignature(),
        strategyMap->generateLambdaExpressionScopeParameter(lambdaExpression->getCapturedValueIds()),
        returnType
    ));

}