//
// Created by Johny Georges on 2025-06-21.
//

#include "ref-array-access-expression-ir-strategy.h"
#include "../../../../ir-nodes/ir-expression-nodes/ir-literal-expression-node.h"
#include "../../../../utils/ir-instruction-node-factory/ir-instruction-node-factory.h"

IRRefArrayAccessExpressionNode* RefArrayAccessExpressionIRStrategy::generate(ASTArrayAccessExpressionNode* node, IRGenerator* irGenerator, IRLookupTable* scope, IRContext* irContext, IROperationType irOperationType) {
    auto sourceValue = irGenerator->generateFor(node->getSource(), scope, irContext, IR_OPERAND_POINTER_OP);
    auto indexValue = irGenerator->generateFor(node->getIndex()->getIndex(), scope, irContext, IR_OPERAND_VALUE_OP);
    auto irArrayElementType = irGenerator->generateTypeFor(node->getTypeSignature(), scope, irContext);
    auto irType = irGenerator->generateIrRefArrayAccessType(irArrayElementType);
    auto sourceAllocation = IRInstructionNodeFactory::create(irType);
    return new IRRefArrayAccessExpressionNode(node, sourceValue, indexValue, irType, sourceAllocation);
}

