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

#include "function-invocation-expression-type-signature-strategy.h"
#include "../../../../../../../shared/utils/function-id-generator/function-id-generator.h"
#include "../../../../../../../shared/utils/logger/logger.h"

void FunctionInvocationExpressionTypeSignatureStrategy::assign(std::shared_ptr<ASTFunctionInvocationExpressionNode> functionInvocationExpression, std::shared_ptr<TypeSignatureContext> context, std::shared_ptr<TypeSignatureLookupTable> typeSignatureLookupTable, TypeSignatureStrategyProvider* strategyMap) {

    auto id = functionInvocationExpression->getFunction()->getId();
    // if the name refers to a lambda
    auto lambdaTypeSignature = typeSignatureLookupTable->find(functionInvocationExpression->getFunction()->getModuleId(), id);
    if (lambdaTypeSignature->isInvocable()) {
        auto invocableTypeSignature = std::dynamic_pointer_cast<InvocableTypeSignature>(lambdaTypeSignature);
        strategyMap->assignTypeSignatureFor(functionInvocationExpression->getArguments(), std::make_shared<TypeSignatureContext>(invocableTypeSignature->getParameterTypes()), typeSignatureLookupTable);
        functionInvocationExpression->getFunction()->setId(id);
        functionInvocationExpression->getFunction()->setTypeSignature(invocableTypeSignature);
        functionInvocationExpression->setTypeSignature(
            std::make_shared<FunctionInvocationTypeSignature>(invocableTypeSignature)
        );
        return;
    }


    // if the name refers to a function or procedure
    auto functionTypeSignatureMap = typeSignatureLookupTable->getGlobalFunction(functionInvocationExpression->getFunction()->getModuleId(), id);
    if (functionTypeSignatureMap) {
        for (auto keyValue : *functionTypeSignatureMap.value()) {
            auto invocableTypeSignature = keyValue.second;
            strategyMap->assignTypeSignatureFor(functionInvocationExpression->getArguments(), std::make_shared<TypeSignatureContext>(invocableTypeSignature->getParameterTypes()), typeSignatureLookupTable);
            if (invocableTypeSignature->doArgumentsMatchParameters(functionInvocationExpression->getArguments()->getArgumentListTypeSignature())) {
                functionInvocationExpression->getFunction()->setId(id);
                functionInvocationExpression->getFunction()->setTypeSignature(invocableTypeSignature);
                functionInvocationExpression->setTypeSignature(
                    std::make_shared<FunctionInvocationTypeSignature>(invocableTypeSignature)
                );
                return;
            }
        }
    }

    auto functionOverride = typeSignatureLookupTable->findGlobalFunctionOverride(id);
    if (functionOverride) {
        strategyMap->assignTypeSignatureFor(functionInvocationExpression->getArguments(), context, typeSignatureLookupTable);
        auto matchedTypeSignature = functionOverride.value()->findMatchFor(functionInvocationExpression->getArguments()->getArgumentListTypeSignature());
        if (matchedTypeSignature) {
            functionInvocationExpression->getFunction()->setId(matchedTypeSignature.value().first);
            functionInvocationExpression->getFunction()->setTypeSignature(matchedTypeSignature.value().second);
            functionInvocationExpression->setTypeSignature(
                std::make_shared<FunctionInvocationTypeSignature>(matchedTypeSignature.value().second)
            );
            return;
        }
    }
    functionInvocationExpression->setTypeSignature(std::make_shared<FunctionInvocationTypeSignature>());
}