//
// Created by Johny Georges on 2026-07-13.
//

#include "share-expression-ir-strategy.h"
#include "../../../../ir-nodes/ir-expression-nodes/ir-literal-expression-node.h"
#include "../../../../utils/ir-instruction-node-factory/ir-instruction-node-factory.h"

std::shared_ptr<IRShareExpressionNode> ShareExpressionIRStrategy::generate(std::shared_ptr<ASTShareExpressionNode> node, std::shared_ptr<IRGenerator> irGenerator, std::shared_ptr<IRLookupTable> scope, std::shared_ptr<IRContext> irContext, std::shared_ptr<IROperation> irOperation) {
    auto irExpressionNode = irGenerator->generateFor(node->getExpressionNode(), scope, irContext, std::make_shared<IROperation>(IR_SHARED_VALUE_ASSIGNMENT_OP));
    irExpressionNode->markAsAssigned();
    auto irType = irGenerator->generateTypeFor(node->getSharedTypeSignature(), scope, irContext);
    auto allocation = IRInstructionNodeFactory::create(irGenerator->generateIrPointerType(irType));
    if (irExpressionNode->getSourceAllocation()) {
        allocation->setParentAllocation(irExpressionNode->getSourceAllocation().value());
    }
    auto arcAllocation = irGenerator->generateArcAllocation(irContext);
    return std::make_shared<IRShareExpressionNode>(node, irExpressionNode, irType, allocation, arcAllocation);
}