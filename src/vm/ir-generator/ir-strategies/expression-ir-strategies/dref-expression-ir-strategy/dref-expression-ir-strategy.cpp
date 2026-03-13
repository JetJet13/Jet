//
// Created by Johny Georges on 2025-02-10.
//

#include "dref-expression-ir-strategy.h"
#include "../../../../utils/ir-instruction-node-factory/ir-instruction-node-factory.h"
#include "../../../../ir-nodes/ir-expression-nodes/ir-dref-expression-node.h"

IRExpressionNode* DrefExpressionIRStrategy::generate(ASTDrefExpressionNode* node, IRGenerator* irGenerator, IRLookupTable* scope, IRContext* irContext, IROperation* irOperation) {
    auto irExpressionNode = irGenerator->generateFor(node->getExpressionNode(), scope, irContext, irOperation);
    auto irType = irGenerator->generateTypeFor(node->getTypeSignature(), scope, irContext);
    auto allocation = this->generateAllocation(node, irType, irGenerator, irContext, irOperation);
    return new IRDrefExpressionNode(node, irExpressionNode, irType, allocation);
}

IRInstructionNode* DrefExpressionIRStrategy::generateAllocation(ASTDrefExpressionNode* node, IRType* irType, IRGenerator* irGenerator, IRContext* irContext, IROperation* irOperation) {
    return IRInstructionNodeFactory::create(irGenerator->generateIrPointerType(irType));
}