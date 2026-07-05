//
// Created by Johny Georges on 2024-12-14.
//

#include "class-property-access-expression-ir-strategy.h"
#include "../../../../../shared/utils/logger/logger.h"

IRClassPropertyAccessExpressionNode* ClassPropertyAccessExpressionIRStrategy::generate(std::shared_ptr<ASTClassPropertyAccessExpressionNode> node, IRGenerator* irGenerator, IRLookupTable* scope, IRContext* irContext, IROperation* irOperation) {
    auto classScope = scope->getClassScope().value();
    auto sourceType = std::dynamic_pointer_cast<IRStructRefType>(classScope->getIRType()->getUnderlyingType());
    auto targetKey = node->getPropertyName();
    auto targetIndex = sourceType->getStructIRType()->getIndexForKey(targetKey);
    auto irType = irGenerator->generateTypeFor(node->getTypeSignature(), scope, irContext);
    return new IRClassPropertyAccessExpressionNode(node, classScope, targetKey, targetIndex, irGenerator->generateIntConstant(targetIndex), irType);
}