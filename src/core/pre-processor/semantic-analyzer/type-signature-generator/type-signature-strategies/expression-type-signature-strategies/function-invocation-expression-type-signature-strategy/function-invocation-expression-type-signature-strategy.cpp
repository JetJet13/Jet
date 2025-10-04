//
// Created by Johny Georges on 2024-05-08.
//

#include "function-invocation-expression-type-signature-strategy.h"
#include "../../../../../../../shared/utils/function-id-generator/function-id-generator.h"
#include "../../../../../../../shared/utils/logger/logger.h"

void FunctionInvocationExpressionTypeSignatureStrategy::assign(ASTFunctionInvocationExpressionNode* functionInvocationExpression, TypeSignatureLookupTable* typeSignatureLookupTable, TypeSignatureStrategyProvider* strategyMap) {
    strategyMap->assignTypeSignatureFor(functionInvocationExpression->getArguments(), typeSignatureLookupTable);
    // if the function refers to a local lambda
    auto typeSignature = typeSignatureLookupTable->find(functionInvocationExpression->getFunction()->getId());
    if (typeSignature->isInvocable()) {
        functionInvocationExpression->getFunction()->setTypeSignature(typeSignature);
        functionInvocationExpression->setTypeSignature(
                new FunctionInvocationTypeSignature((InvocableTypeSignature*)typeSignature)
        );
        return;
    }

    // if the function refers to a function or procedure
    auto id = FunctionIdGenerator::generateFor(functionInvocationExpression);
    auto functionTypeSignature = typeSignatureLookupTable->find(id);
    if (functionTypeSignature->isInvocable()) {
        functionInvocationExpression->getFunction()->setId(id);
        functionInvocationExpression->getFunction()->setTypeSignature(functionTypeSignature);
        functionInvocationExpression->setTypeSignature(
            new FunctionInvocationTypeSignature((InvocableTypeSignature*)functionTypeSignature)
        );
        return;
    }
    auto functionOverride = typeSignatureLookupTable->findGlobalFunctionOverride(FunctionIdGenerator::getNameFromId(id));
    if (functionOverride) {
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
    typeSignatureLookupTable->dump();
    Logger::log("function not found", id);
    functionInvocationExpression->setTypeSignature(new FunctionInvocationTypeSignature());
}