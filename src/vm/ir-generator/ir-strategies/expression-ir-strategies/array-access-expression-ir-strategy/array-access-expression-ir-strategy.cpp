//
// Created by Johny Georges on 2024-06-21.
//

#include "array-access-expression-ir-strategy.h"
#include "../../../ir-util-functions/array-access-ir-function/array-access-ir-function.h"
#include "../../../../utils/ir-instruction-node-factory/ir-instruction-node-factory.h"
#include "../../../../../shared/utils/logger/logger.h"

IRArrayAccessExpressionNode* ArrayAccessExpressionIRStrategy::ArrayAccessExpressionIRStrategy::generate(ASTArrayAccessExpressionNode* node, IRGenerator* irGenerator, IRLookupTable* scope, IRContext* irContext, IROperationType irOperationType) {
    auto sourceValue = irGenerator->generateFor(node->getSource(), scope, irContext, IR_OPERAND_VALUE_OP);
    auto indexValue = irGenerator->generateFor(node->getIndex()->getIndex(), scope, irContext, IR_OPERAND_VALUE_OP);
    auto irType = irGenerator->generateTypeFor(node->getTypeSignature(), scope, irContext);
    auto sourceAllocation = IRInstructionNodeFactory::create(irGenerator->generateIrPointerType(irType));
    return new IRArrayAccessExpressionNode(node, sourceValue, indexValue, irType, sourceAllocation);
}