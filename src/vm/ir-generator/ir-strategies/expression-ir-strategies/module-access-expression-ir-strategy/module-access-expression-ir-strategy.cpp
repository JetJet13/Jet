//
// Created by Johny Georges on 2026-03-27.
//

#include "module-access-expression-ir-strategy.h"

IRExpressionNode* ModuleAccessExpressionIRStrategy::generate(ASTModuleAccessExpressionNode* node, IRGenerator* irGenerator, IRLookupTable* scope, IRContext* irContext, IROperation* irOperation) {
    auto moduleName = node->getSource()->getSource()->getIdentifierNode()->getId();
    auto targetKey = node->getTarget()->getTarget()->getIdentifierNode()->getId();
    auto valueName = moduleName + "." + targetKey;
    auto sourceValue = irContext->getModule()->getGlobalVariable(valueName);
    auto irType = irGenerator->generateTypeFor(node->getTypeSignature(), scope, irContext);
    return new IRModuleAccessExpressionNode(node, sourceValue, irType);
}