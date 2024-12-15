//
// Created by Johny Georges on 2024-12-14.
//

#include "class-property-access-expression-ir-strategy.h"
#include "../../../../utils/ir-instruction-node-factory/ir-instruction-node-factory.h"
#include "../../../../../shared/utils/logger/logger.h"

IRClassPropertyAccessExpressionNode* ClassPropertyAccessExpressionIRStrategy::generate(ASTClassPropertyAccessExpressionNode* node, std::unique_ptr<llvm::LLVMContext>* context, IRGenerator* irGenerator, IRLookupTable* scope, IRModuleNode* irModule, IROperationType irOperationType) {
    auto classScope = scope->getClassScope().value();
    auto sourceType = (IRStructType*)classScope->getIRType()->getSourceType();
    auto targetKey = node->getPropertyAccess()->getPropertyName()->getId();
    auto targetIndex = sourceType->getIndexForKey(targetKey);
    auto irType = irGenerator->generateTypeFor(node->getTypeSignature());
    return new IRClassPropertyAccessExpressionNode(node, classScope, targetKey, targetIndex, irGenerator->generateIntConstant(targetIndex), irType);
}