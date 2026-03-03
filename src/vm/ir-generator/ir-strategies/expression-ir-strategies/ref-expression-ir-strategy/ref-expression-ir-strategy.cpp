//
// Created by Johny Georges on 2025-02-10.
//

#include "ref-expression-ir-strategy.h"
#include "../../../../ir-nodes/ir-expression-nodes/ir-literal-expression-node.h"
#include "../../../../utils/ir-instruction-node-factory/ir-instruction-node-factory.h"

IRRefExpressionNode* RefExpressionIRStrategy::generate(ASTRefExpressionNode* node, IRGenerator* irGenerator, IRLookupTable* scope, IRContext* irContext, IROperation* irOperation) {
    auto irExpressionNode = irGenerator->generateFor(node->getExpressionNode(), scope, irContext, new IROperation(IR_REF_ASSIGNMENT_OP));
    auto irType = irGenerator->generateTypeFor(node->getTypeSignature(), scope, irContext);
    auto allocation = this->generateAllocation(node, irType, irGenerator, irContext, irOperation);
    if (irExpressionNode->getSourceAllocation()) {
        allocation->setParentAllocation(irExpressionNode->getSourceAllocation().value());
    }
    auto arcAllocation = irGenerator->generateArcAllocation(irContext);
    return new IRRefExpressionNode(node, irExpressionNode, irType, allocation, arcAllocation);
}

IRInstructionNode* RefExpressionIRStrategy::generateAllocation(ASTRefExpressionNode* node, IRRefType* irType, IRGenerator* irGenerator, IRContext* irContext, IROperation* irOperation) {
    return IRInstructionNodeFactory::create(irGenerator->generateIrPointerType(irType));
}