//
// Created by Johny Georges on 2025-02-10.
//

#include "ref-expression-ir-strategy.h"
#include "../../../../ir-nodes/ir-expression-nodes/ir-literal-expression-node.h"
#include "../../../../utils/ir-instruction-node-factory/ir-instruction-node-factory.h"

std::shared_ptr<IRRefExpressionNode> RefExpressionIRStrategy::generate(std::shared_ptr<ASTRefExpressionNode> node, IRGenerator* irGenerator, std::shared_ptr<IRLookupTable> scope, IRContext* irContext, IROperation* irOperation) {
    auto irExpressionNode = irGenerator->generateFor(node->getExpressionNode(), scope, irContext, new IROperation(IR_REF_ASSIGNMENT_OP));
    irExpressionNode->markAsAssigned();
    auto irType = irGenerator->generateTypeFor(node->getRefTypeSignature(), scope, irContext);
    auto allocation = this->generateAllocation(node, irType, irGenerator, irContext, irOperation);
    if (irExpressionNode->getSourceAllocation()) {
        allocation->setParentAllocation(irExpressionNode->getSourceAllocation().value());
    }
    auto arcAllocation = irGenerator->generateArcAllocation(irContext);
    return std::make_shared<IRRefExpressionNode>(node, irExpressionNode, irType, allocation, arcAllocation);
}

std::shared_ptr<IRInstructionNode> RefExpressionIRStrategy::generateAllocation(std::shared_ptr<ASTRefExpressionNode> node, std::shared_ptr<IRRefType> irType, IRGenerator* irGenerator, IRContext* irContext, IROperation* irOperation) {
    return IRInstructionNodeFactory::create(irGenerator->generateIrPointerType(irType));
}