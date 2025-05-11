//
// Created by Johny Georges on 2025-03-29.
//

#include "sref-expression-ir-strategy.h"
#include "../../../../utils/ir-instruction-node-factory/ir-instruction-node-factory.h"
#include "../../../../ir-nodes/ir-expression-nodes/ir-sref-expression-node.h"

IRExpressionNode* SrefExpressionIRStrategy::generate(ASTSrefExpressionNode* node, IRGenerator* irGenerator, IRLookupTable* scope, IRContext* irContext, IROperationType irOperationType) {
    auto irExpressionNode = irGenerator->generateFor(node->getExpressionNode(), scope, irContext, irOperationType);
    auto irType = irGenerator->generateTypeFor(node->getTypeSignature(), scope, irContext);
    auto allocation = this->generateAllocation(node, irType, irGenerator, irContext, irOperationType);
    if (irExpressionNode->getSourceAllocation()) {
        allocation->setParentAllocation(irExpressionNode->getSourceAllocation().value());
    }
    return new IRSrefExpressionNode(node, irExpressionNode, irType, allocation);
}

IRInstructionNode* SrefExpressionIRStrategy::generateAllocation(ASTSrefExpressionNode* node, IRRefType* irType, IRGenerator* irGenerator, IRContext* irContext, IROperationType irOperationType) {
    if (node->isReferenced()) {
        auto malloc = llvm::CallInst::Create(
                irContext->getIRModule()->getMallocFunction()->getFunctionType(),
                irContext->getIRModule()->getMallocFunction(),
                { irGenerator->generateIntConstant(irType->getSizeInBytes()) },
                ""
        );
        return IRInstructionNodeFactory::create(
                new llvm::BitCastInst(malloc, irType->getType()),
                irGenerator->generateIrPointerType(irType),
                { malloc }
        );
    }
    return IRInstructionNodeFactory::create(irGenerator->generateIrPointerType(irType));
}