//
// Created by Johny Georges on 2024-06-21.
//

#include "array-access-expression-ir-strategy.h"
#include "../../../ir-util-functions/array-access-ir-function/array-access-ir-function.h"
#include "../../../../utils/ir-instruction-node-factory/ir-instruction-node-factory.h"
#include "../../../../../shared/utils/logger/logger.h"

std::shared_ptr<IRArrayAccessExpressionNode> ArrayAccessExpressionIRStrategy::ArrayAccessExpressionIRStrategy::generate(std::shared_ptr<ASTArrayAccessExpressionNode> node, IRGenerator* irGenerator, std::shared_ptr<IRLookupTable> scope, std::shared_ptr<IRContext> irContext, std::shared_ptr<IROperation> irOperation) {
    auto sourceValue = irGenerator->generateFor(node->getSource(), scope, irContext, std::make_shared<IROperation>(IR_OPERAND_POINTER_OP));
    auto indexValue = irGenerator->generateFor(node->getIndex()->getIndex(), scope, irContext, std::make_shared<IROperation>(IR_OPERAND_VALUE_OP));
    auto irType = irGenerator->generateTypeFor(node->getTypeSignature(), scope, irContext);
    auto sourceAllocation = IRInstructionNodeFactory::create(irGenerator->generateIrPointerType(irType));
    return std::make_shared<IRArrayAccessExpressionNode>(node, sourceValue, indexValue, irType, sourceAllocation);
}