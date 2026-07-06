//
// Created by Johny Georges on 2026-03-27.
//

#include "module-access-expression-ir-strategy.h"
#include "../../../../../shared/utils/function-id-generator/function-id-generator.h"

std::shared_ptr<IRExpressionNode> ModuleAccessExpressionIRStrategy::generate(std::shared_ptr<ASTModuleAccessExpressionNode> node, IRGenerator* irGenerator, IRLookupTable* scope, IRContext* irContext, IROperation* irOperation) {
    auto sourceValue = scope->findGlobalVariable(node->getModuleName(), node->getModuleTargetName());
    if (!sourceValue && node->getTypeSignature()->isInvocable()) {
        auto invocableTypeSignature = std::dynamic_pointer_cast<InvocableTypeSignature>(node->getTypeSignature());
        auto lambdaValueName = FunctionIdGenerator::generateFor(node->getModuleTargetName(), invocableTypeSignature);
        sourceValue = scope->findGlobalVariable(node->getModuleId(), lambdaValueName);
    }

    return std::make_shared<IRModuleAccessExpressionNode>(node, sourceValue.value()->getValue(), sourceValue.value()->getIRType());
}