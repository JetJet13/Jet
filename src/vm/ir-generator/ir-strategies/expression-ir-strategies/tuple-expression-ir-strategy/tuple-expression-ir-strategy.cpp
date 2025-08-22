//
// Created by Johny Georges on 2024-06-25.
//

#include "tuple-expression-ir-strategy.h"
#include "../../../../utils/ir-instruction-node-factory/ir-instruction-node-factory.h"

IRTupleExpressionNode* TupleExpressionIRStrategy::generate(ASTTupleExpressionNode* node, IRGenerator* irGenerator, IRLookupTable* scope, IRContext* irContext, IROperationType irOperationType) {
    auto irType = irGenerator->generateTypeFor(node->getTypeSignature(), scope, irContext);
    auto tupleValues = std::vector<IRExpressionNode*>();
    for (auto tupleItem : node->getItems()) {
        auto irNode = irGenerator->generateFor(tupleItem->getItem(), scope, irContext, irOperationType);
        tupleValues.push_back(irNode);
    }

    return new IRTupleExpressionNode(
            node,
            this->generateTupleAllocation(node, irType, irGenerator, irContext, irOperationType),
            irType,
            tupleValues
    );
}

IRInstructionNode* TupleExpressionIRStrategy::generateTupleAllocation(ASTTupleExpressionNode* node, IRStructType* irType, IRGenerator* irGenerator, IRContext* irContext, IROperationType irOperationType) {
    if (node->isReferenced() || irOperationType == IR_COPY_GLOBAL_ASSIGNMENT_OP || irOperationType == IR_REF_GLOBAL_ASSIGNMENT_OP) {
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