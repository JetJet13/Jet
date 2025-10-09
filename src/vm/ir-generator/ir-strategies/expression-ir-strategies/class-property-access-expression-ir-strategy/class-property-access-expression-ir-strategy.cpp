//
// Created by Johny Georges on 2024-12-14.
//

#include "class-property-access-expression-ir-strategy.h"
#include "../../../../../shared/utils/logger/logger.h"

IRClassPropertyAccessExpressionNode* ClassPropertyAccessExpressionIRStrategy::generate(ASTClassPropertyAccessExpressionNode* node, IRGenerator* irGenerator, IRLookupTable* scope, IRContext* irContext, IROperation* irOperation) {
    auto classScope = scope->getClassScope().value();
    auto sourceType = (IRStructType*)classScope->getIRType()->getUnderlyingType();
    auto targetKey = node->getPropertyAccess()->getPropertyName()->getId();
    auto targetIndex = sourceType->getIndexForKey(targetKey);
    auto irType = irGenerator->generateTypeFor(node->getTypeSignature(), scope, irContext);
    return new IRClassPropertyAccessExpressionNode(node, classScope, targetKey, targetIndex, irGenerator->generateIntConstant(targetIndex), irType);
}