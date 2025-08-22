//
// Created by Johny Georges on 2025-02-10.
//

#include "dref-expression-ir-strategy.h"
#include "../../../../utils/ir-instruction-node-factory/ir-instruction-node-factory.h"
#include "../../../../ir-nodes/ir-expression-nodes/ir-dref-expression-node.h"

IRExpressionNode* DrefExpressionIRStrategy::generate(ASTDrefExpressionNode* node, IRGenerator* irGenerator, IRLookupTable* scope, IRContext* irContext, IROperationType irOperationType) {
    auto irExpressionNode = irGenerator->generateFor(node->getExpressionNode(), scope, irContext, irOperationType);
    auto irType = irGenerator->generateTypeFor(node->getTypeSignature(), scope, irContext);
    auto allocation = this->generateAllocation(node, irType, irGenerator, irContext, irOperationType);
    if (irExpressionNode->getSourceAllocation()) {
        allocation->setParentAllocation(irExpressionNode->getSourceAllocation().value());
    }
    return new IRDrefExpressionNode(node, irExpressionNode, irType, allocation);
}

IRInstructionNode* DrefExpressionIRStrategy::generateAllocation(ASTDrefExpressionNode* node, IRType* irType, IRGenerator* irGenerator, IRContext* irContext, IROperationType irOperationType) {
    if (node->isReferenced()) {
        auto malloc = llvm::CallInst::Create(
                irContext->getIRModule()->getMallocFunction()->getFunctionType(),
                irContext->getIRModule()->getMallocFunction(),
                { irGenerator->generateInt64Constant(irType->getSizeInBytes()) },
                ""
        );
        return IRInstructionNodeFactory::create(
                malloc,
                irGenerator->generateIrPointerType(irType)
        );
    }
    return IRInstructionNodeFactory::create(irGenerator->generateIrPointerType(irType));
}