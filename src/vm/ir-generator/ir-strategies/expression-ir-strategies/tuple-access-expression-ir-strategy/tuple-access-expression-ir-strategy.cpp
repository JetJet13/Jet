//
// Created by Johny Georges on 2024-10-09.
//

#include "tuple-access-expression-ir-strategy.h"
#include "../../../../utils/ir-instruction-node-factory/ir-instruction-node-factory.h"
#include "../../../../../shared/utils/logger/logger.h"

std::shared_ptr<IRTupleAccessExpressionNode> TupleAccessExpressionIRStrategy::generate(std::shared_ptr<ASTTupleAccessExpressionNode> node, std::shared_ptr<IRGenerator> irGenerator, std::shared_ptr<IRLookupTable> scope, std::shared_ptr<IRContext> irContext, std::shared_ptr<IROperation> irOperation) {
    auto sourceValue = irGenerator->generateFor(node->getSource()->getSource(), scope, irContext, (std::make_shared<IROperation>(IR_OPERAND_POINTER_OP))->markAsUnderlying());
    auto sourceType = std::dynamic_pointer_cast<IRStructRefType>(sourceValue->getUnderlyingIRType());
    auto targetIndex = node->getIndex()->getIndexValue();
    auto irType = irGenerator->generateTypeFor(node->getTypeSignature(), scope, irContext);
    auto sourceAllocation = IRInstructionNodeFactory::create(sourceType->getStructIRType()->getIRTypeByIndex(targetIndex));
    return std::make_shared<IRTupleAccessExpressionNode>(node, sourceValue, targetIndex, irGenerator->generateIntConstant(targetIndex), irType, sourceAllocation);
}