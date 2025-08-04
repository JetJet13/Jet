//
// Created by Johny Georges on 2024-05-08.
//

#include "function-invocation-expression-type-signature-strategy.h"
#include "../../../../../../../shared/utils/function-id-generator/function-id-generator.h"
#include "../../../../../../../shared/utils/logger/logger.h"


void FunctionInvocationExpressionTypeSignatureStrategy::assign(ASTFunctionInvocationExpressionNode* functionInvocationExpression, TypeSignatureLookupTable* typeSignatureLookupTable, TypeSignatureStrategyProvider* strategyMap) {
    strategyMap->assignTypeSignatureFor(functionInvocationExpression->getArguments(), typeSignatureLookupTable);
    auto id = FunctionIdGenerator::generateFor(functionInvocationExpression);
    Logger::log("function invocation", id);
    auto typeSignature = typeSignatureLookupTable->find(id);
    if (typeSignature->isInvocable()) {
        functionInvocationExpression->getFunction()->setId(id);
        functionInvocationExpression->getFunction()->setTypeSignature(typeSignature);
        functionInvocationExpression->setTypeSignature(
            new FunctionInvocationTypeSignature((InvocableTypeSignature*)typeSignature)
        );
        return;
    }
    auto functionOverride = typeSignatureLookupTable->findGlobalFunctionOverride(FunctionIdGenerator::getNameFromId(id));
    if (functionOverride) {
        auto matchedTypeSignature = functionOverride.value()->findMatchFor(functionInvocationExpression->getArguments()->getTypeSignature());
        if (matchedTypeSignature) {
            Logger::log("found matched type signature", matchedTypeSignature.value().first, id);
            functionInvocationExpression->getFunction()->setId(matchedTypeSignature.value().first);
            functionInvocationExpression->getFunction()->setTypeSignature(matchedTypeSignature.value().second);
            functionInvocationExpression->setTypeSignature(
                new FunctionInvocationTypeSignature(matchedTypeSignature.value().second)
            );
            return;
        }
    }
    functionInvocationExpression->setTypeSignature(new FunctionInvocationTypeSignature());
}