//
// Created by Johny Georges on 2026-03-27.
//

#include "module-access-expression-ir-strategy.h"
#include "../../../../../shared/utils/function-id-generator/function-id-generator.h"

IRExpressionNode* ModuleAccessExpressionIRStrategy::generate(ASTModuleAccessExpressionNode* node, IRGenerator* irGenerator, IRLookupTable* scope, IRContext* irContext, IROperation* irOperation) {
    auto moduleName = node->getSource()->getSource()->getIdentifierNode()->getId();
    auto targetKey = node->getTarget()->getTarget()->getIdentifierNode()->getId();
    auto valueName = moduleName + "." + targetKey;
    auto sourceValue = scope->findGlobalVariable(valueName);
    if (!sourceValue && node->getTypeSignature()->isInvocable()) {
        auto invocableTypeSignature = (InvocableTypeSignature*)node->getTypeSignature();
        auto lambdaValueName = moduleName + "." + FunctionIdGenerator::generateFor(targetKey, invocableTypeSignature);
        sourceValue = scope->findGlobalVariable(lambdaValueName);
    }

    auto irType = scope->findGlobalType(valueName);
    if (!irType) {
        irType = irGenerator->generateTypeFor(node->getTypeSignature(), scope, irContext);
    }
    return new IRModuleAccessExpressionNode(node, sourceValue.value()->getValue(), irType.value());
}