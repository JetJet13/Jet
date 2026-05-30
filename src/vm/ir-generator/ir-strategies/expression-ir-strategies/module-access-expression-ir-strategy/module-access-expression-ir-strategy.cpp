//
// Created by Johny Georges on 2026-03-27.
//

#include "module-access-expression-ir-strategy.h"
#include "../../../../../shared/utils/function-id-generator/function-id-generator.h"

IRExpressionNode* ModuleAccessExpressionIRStrategy::generate(ASTModuleAccessExpressionNode* node, IRGenerator* irGenerator, IRLookupTable* scope, IRContext* irContext, IROperation* irOperation) {
    auto sourceValue = scope->findGlobalVariable(node->getModuleName(), node->getModuleTargetName());
    if (!sourceValue && node->getTypeSignature()->isInvocable()) {
        auto invocableTypeSignature = (InvocableTypeSignature*)node->getTypeSignature();
        auto lambdaValueName = FunctionIdGenerator::generateFor(node->getModuleTargetName(), invocableTypeSignature);
        sourceValue = scope->findGlobalVariable(node->getModuleId(), lambdaValueName);
    }

    return new IRModuleAccessExpressionNode(node, sourceValue.value()->getValue(), sourceValue.value()->getIRType()->getUnderlyingType());
}