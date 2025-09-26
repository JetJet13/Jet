//
// Created by Johny Georges on 2024-07-16.
//

#include "object-access-expression-ir-strategy.h"
#include "../../../../utils/ir-instruction-node-factory/ir-instruction-node-factory.h"
#include "../../../../../shared/utils/logger/logger.h"

IRObjectAccessExpressionNode* ObjectAccessExpressionIRStrategy::generate(ASTObjectAccessExpressionNode* node, IRGenerator* irGenerator, IRLookupTable* scope, IRContext* irContext, IROperation* irOperation) {
    auto sourceValue = irGenerator->generateFor(node->getSource()->getSource(), scope, irContext, irOperation);
    auto sourceType = (IRStructType*)sourceValue->getUnderlyingIRType();
    auto targetKey = node->getTarget()->getTarget()->getIdentifierNode()->getId();
    auto targetIndex = sourceType->getIndexForKey(targetKey);
    auto irType = irGenerator->generateTypeFor(node->getTypeSignature(), scope, irContext);
    auto sourceAllocation = IRInstructionNodeFactory::create(irGenerator->generateIrPointerType(irType));
    return new IRObjectAccessExpressionNode(node, sourceValue, targetKey, targetIndex, irGenerator->generateIntConstant(targetIndex), irType, sourceAllocation);
}