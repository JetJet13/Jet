//
// Created by Johny Georges on 2024-06-25.
//

#include "tuple-expression-ir-strategy.h"
#include "../../../../utils/ir-instruction-node-factory/ir-instruction-node-factory.h"

std::shared_ptr<IRTupleExpressionNode> TupleExpressionIRStrategy::generate(std::shared_ptr<ASTTupleExpressionNode> node, std::shared_ptr<IRGenerator> irGenerator, std::shared_ptr<IRLookupTable> scope, std::shared_ptr<IRContext> irContext, std::shared_ptr<IROperation> irOperation) {
    auto irType = irGenerator->generateTypeFor(node->getTupleTypeSignature(), scope, irContext);
    auto tupleValues = std::vector<std::shared_ptr<IRExpressionNode>>();
    for (unsigned long i = 0; i < node->numItems(); ++i) {
        auto tupleItem = node->getItems()->at(i);
        auto irNode = irGenerator->generateFor(tupleItem->getItem(), scope, irContext, irOperation);
        irNode->markAsAssigned();
        tupleValues.push_back(irNode);
    }
    auto tupleAllocation = this->generateTupleAllocation(irType->getStructIRType(), irGenerator, irContext);
    auto tuplePointerAllocation = this->generateTuplePointerAllocation(node, irType, irGenerator, irContext, irOperation);
    tuplePointerAllocation->setParentAllocation(tupleAllocation);
    return std::make_shared<IRTupleExpressionNode>(
            node,
            tuplePointerAllocation,
            irGenerator->generateArcAllocation(irContext),
            irType,
            tupleValues
    );
}

std::shared_ptr<IRInstructionNode> TupleExpressionIRStrategy::generateTupleAllocation(std::shared_ptr<IRStructType> irType, std::shared_ptr<IRGenerator> irGenerator, std::shared_ptr<IRContext> irContext) {
    auto malloc = llvm::CallInst::Create(
            irContext->getIRModule()->getMallocFunction(),
            {
                irGenerator->generateInt64Constant(1),
                irGenerator->generateInt64Constant(irType->getSizeInBytes())
            },
            ""
    );
    return IRInstructionNodeFactory::create(
            malloc,
            irGenerator->generateIrPointerType(irType)
    );
}


std::shared_ptr<IRInstructionNode> TupleExpressionIRStrategy::generateTuplePointerAllocation(std::shared_ptr<ASTTupleExpressionNode> node, std::shared_ptr<IRStructRefType> irType, std::shared_ptr<IRGenerator> irGenerator, std::shared_ptr<IRContext> irContext, std::shared_ptr<IROperation> irOperation) {
    return IRInstructionNodeFactory::create(irGenerator->generateIrPointerType(irType));
}