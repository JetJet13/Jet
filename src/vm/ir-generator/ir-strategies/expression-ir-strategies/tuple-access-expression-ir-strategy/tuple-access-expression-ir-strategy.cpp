//
// Created by Johny Georges on 2024-10-09.
//

#include "tuple-access-expression-ir-strategy.h"
#include "../../../../utils/ir-instruction-node-factory/ir-instruction-node-factory.h"
#include "../../../../../shared/utils/logger/logger.h"

IRTupleAccessExpressionNode* TupleAccessExpressionIRStrategy::generate(ASTTupleAccessExpressionNode* node, IRGenerator* irGenerator, IRLookupTable* scope, IRContext* irContext, IROperationType irOperationType) {
    auto sourceValue = irGenerator->generateFor(node->getSource()->getSource(), scope, irContext, irOperationType);
    auto sourceType = (IRStructType*)sourceValue->getIRType()->getSourceType();
    auto targetIndex = node->getIndex()->getIndexValue();
    auto irType = irGenerator->generateTypeFor(node->getTypeSignature(), scope, irContext);
    auto sourceAllocation = IRInstructionNodeFactory::create(sourceType);
    return new IRTupleAccessExpressionNode(node, sourceValue, targetIndex, irGenerator->generateIntConstant(targetIndex), irType, sourceAllocation);
}