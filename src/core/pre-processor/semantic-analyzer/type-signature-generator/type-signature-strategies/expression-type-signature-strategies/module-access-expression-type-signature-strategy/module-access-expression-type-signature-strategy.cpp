//
// Created by Johny Georges on 2024-11-07.
//

#include "module-access-expression-type-signature-strategy.h"
#include "../../../../../../../shared/utils/function-id-generator/function-id-generator.h"

void ModuleAccessExpressionTypeSignatureStrategy::assign(std::shared_ptr<ASTModuleAccessExpressionNode> moduleAccessExpression, std::shared_ptr<TypeSignatureContext> context, std::shared_ptr<TypeSignatureLookupTable> scope, TypeSignatureStrategyProvider* strategyMap) {
    auto typeSignature = scope->find(moduleAccessExpression->getModuleName(), moduleAccessExpression->getModuleTargetName());
    if (typeSignature->isUnknown() && context->getTypeSignature() && context->getTypeSignature().value()->isInvocable()) {
        auto invocableTypeSignature = std::dynamic_pointer_cast<InvocableTypeSignature>(context->getTypeSignature().value());
        auto functionTypeSignature = scope->findGlobalFunction(moduleAccessExpression->getModuleId(), moduleAccessExpression->getModuleTargetName(), FunctionIdGenerator::generateFor(invocableTypeSignature));
        if (functionTypeSignature) {
            moduleAccessExpression->setTypeSignature(functionTypeSignature.value()->convertToVariableTypeSignature());
            return;
        }
    }
    moduleAccessExpression->setTypeSignature(typeSignature);
}