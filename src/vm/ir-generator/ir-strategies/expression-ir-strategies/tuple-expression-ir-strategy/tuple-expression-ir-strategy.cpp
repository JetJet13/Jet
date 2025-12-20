//
// Created by Johny Georges on 2024-06-25.
//

#include "tuple-expression-ir-strategy.h"
#include "../../../../utils/ir-instruction-node-factory/ir-instruction-node-factory.h"

IRTupleExpressionNode* TupleExpressionIRStrategy::generate(ASTTupleExpressionNode* node, IRGenerator* irGenerator, IRLookupTable* scope, IRContext* irContext, IROperation* irOperation) {
    auto irType = irGenerator->generateTypeFor(node->getTypeSignature(), scope, irContext);
    auto tupleValues = std::vector<IRExpressionNode*>();
    for (int i = 0; i < node->numItems(); ++i) {
        auto tupleItem = node->getItems()->at(i);
        auto irNode = irGenerator->generateFor(tupleItem->getItem(), scope, irContext, irOperation);
        irNode->markAsAssigned();
        tupleValues.push_back(irNode);
    }
    auto tupleAllocation = this->generateTupleAllocation(irType->getStructIRType(), irGenerator, irContext);
    auto tuplePointerAllocation = this->generateTuplePointerAllocation(node, irType, irGenerator, irContext, irOperation);
    tuplePointerAllocation->setParentAllocation(tupleAllocation);
    return new IRTupleExpressionNode(
            node,
            tuplePointerAllocation,
            irType,
            tupleValues
    );
}

IRInstructionNode* TupleExpressionIRStrategy::generateTupleAllocation(IRStructType* irType, IRGenerator* irGenerator, IRContext* irContext) {
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


IRInstructionNode* TupleExpressionIRStrategy::generateTuplePointerAllocation(ASTTupleExpressionNode* node, IRStructRefType* irType, IRGenerator* irGenerator, IRContext* irContext, IROperation* irOperation) {
    if (node->isReferenced() || irOperation->isCopyGlobal() || irOperation->isRefGlobalAssignment()) {
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