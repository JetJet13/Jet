//
// Created by Johny Georges on 2024-12-14.
//

#include "class-property-access-expression-ir-strategy.h"
#include "../../../../utils/ir-instruction-node-factory/ir-instruction-node-factory.h"
#include "../../../../../shared/utils/logger/logger.h"

IRClassPropertyAccessExpressionNode* ClassPropertyAccessExpressionIRStrategy::generate(ASTClassPropertyAccessExpressionNode* node, IRGenerator* irGenerator, IRLookupTable* scope, IRContext* irContext, IROperationType irOperationType) {
    auto classScope = scope->getClassScope().value();
    auto sourceType = (IRStructType*)classScope->getIRType()->getSourceType()->getSourceType();
    sourceType->print();
    auto targetKey = node->getPropertyAccess()->getPropertyName()->getId();
    auto targetIndex = sourceType->getIndexForKey(targetKey);
    auto irType = irGenerator->generateTypeFor(node->getTypeSignature(), scope, irContext);
    auto sourceAllocation = IRInstructionNodeFactory::create(irGenerator->generateIrPointerType(irType));
    return new IRClassPropertyAccessExpressionNode(node, classScope, targetKey, targetIndex, irGenerator->generateIntConstant(targetIndex), irType, sourceAllocation);
}