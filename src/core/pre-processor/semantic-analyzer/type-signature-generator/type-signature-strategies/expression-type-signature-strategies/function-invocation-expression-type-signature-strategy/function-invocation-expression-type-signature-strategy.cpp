//
// Created by Johny Georges on 2024-05-08.
//

#include "function-invocation-expression-type-signature-strategy.h"
#include "../../../../../../../shared/utils/function-id-generator/function-id-generator.h"
#include "../../../../../../../shared/utils/logger/logger.h"

void FunctionInvocationExpressionTypeSignatureStrategy::assign(ASTFunctionInvocationExpressionNode* functionInvocationExpression, std::shared_ptr<TypeSignatureContext> context, std::shared_ptr<TypeSignatureLookupTable> typeSignatureLookupTable, TypeSignatureStrategyProvider* strategyMap) {

    auto id = functionInvocationExpression->getFunction()->getId();
    // if the name refers to a lambda
    auto lambdaTypeSignature = typeSignatureLookupTable->find(functionInvocationExpression->getFunction()->getModuleId(), id);
    if (lambdaTypeSignature->isInvocable()) {
        auto invocableTypeSignature = (InvocableTypeSignature*)lambdaTypeSignature;
        strategyMap->assignTypeSignatureFor(functionInvocationExpression->getArguments(), std::make_shared<TypeSignatureContext>(invocableTypeSignature->getParameterTypes()), typeSignatureLookupTable);
        functionInvocationExpression->getFunction()->setId(id);
        functionInvocationExpression->getFunction()->setTypeSignature(invocableTypeSignature);
        functionInvocationExpression->setTypeSignature(
            new FunctionInvocationTypeSignature(invocableTypeSignature)
        );
        return;
    }


    // if the name refers to a function or procedure
    auto functionTypeSignatureMap = typeSignatureLookupTable->getGlobalFunction(functionInvocationExpression->getFunction()->getModuleId(), id);
    if (functionTypeSignatureMap) {
        for (auto keyValue : *functionTypeSignatureMap.value()) {
            auto invocableTypeSignature = keyValue.second;
            strategyMap->assignTypeSignatureFor(functionInvocationExpression->getArguments(), std::make_shared<TypeSignatureContext>(invocableTypeSignature->getParameterTypes()), typeSignatureLookupTable);
            if (invocableTypeSignature->doArgumentsMatchParameters(functionInvocationExpression->getArguments()->getTypeSignature())) {
                functionInvocationExpression->getFunction()->setId(id);
                functionInvocationExpression->getFunction()->setTypeSignature(invocableTypeSignature);
                functionInvocationExpression->setTypeSignature(
                    new FunctionInvocationTypeSignature(invocableTypeSignature)
                );
                return;
            }
        }
    }

    auto functionOverride = typeSignatureLookupTable->findGlobalFunctionOverride(id);
    if (functionOverride) {
        strategyMap->assignTypeSignatureFor(functionInvocationExpression->getArguments(), context, typeSignatureLookupTable);
        auto matchedTypeSignature = functionOverride.value()->findMatchFor(functionInvocationExpression->getArguments()->getTypeSignature());
        if (matchedTypeSignature) {
            functionInvocationExpression->getFunction()->setId(matchedTypeSignature.value().first);
            functionInvocationExpression->getFunction()->setTypeSignature(matchedTypeSignature.value().second);
            functionInvocationExpression->setTypeSignature(
                new FunctionInvocationTypeSignature(matchedTypeSignature.value().second)
            );
            return;
        }
    }
    Logger::log("UH OH!!", functionInvocationExpression->getFunction()->getId());
    functionInvocationExpression->setTypeSignature(new FunctionInvocationTypeSignature());
}