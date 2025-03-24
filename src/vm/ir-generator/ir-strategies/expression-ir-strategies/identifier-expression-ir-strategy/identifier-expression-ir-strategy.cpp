//
// Created by Johny Georges on 2024-06-26.
//

#include "identifier-expression-ir-strategy.h"
#include "../../../../utils/data-alignment-generator/data-alignment-generator.h"
#include "../../../../utils/ir-instruction-node-factory/ir-instruction-node-factory.h"
#include "../../../../ir-nodes/ir-expression-nodes/ir-identifier-expression-node.h"

IRExpressionNode* IdentifierExpressionIRStrategy::generate(ASTIdentifierExpressionNode* node, IRGenerator* irGenerator, IRLookupTable* scope, IRContext* irContext, IROperationType irOperationType) {
    auto allocation = scope->findAcrossScopes(node->getIdentifierNode()->getId());
    if (irOperationType == IR_COPY_ASSIGNMENT_OP && allocation.value()->getIRType()->getSourceType()->isArrayPointerType()) {
        return this->generateForAggregate(node, allocation.value(), irGenerator, scope, irContext, irOperationType);
    } else if (irOperationType == IR_COPY_GLOBAL_ASSIGNMENT_OP && allocation.value()->getIRType()->getSourceType()->isArrayPointerType()) {
        return this->generateForGlobalAggregate(node, allocation.value(), irGenerator, scope, irContext, irOperationType);
    }
    return new IRIdentifierExpressionNode(node, allocation.value());

}

IRAggregateIdentifierExpressionNode* IdentifierExpressionIRStrategy::generateForAggregate(ASTIdentifierExpressionNode* node, IRInstructionNode* allocation, IRGenerator* irGenerator, IRLookupTable* scope, IRContext* irContext, IROperationType irOperationType) {
    auto arrayPointerType = (IRArrayPointerType*)allocation->getIRType()->getSourceType();
    auto zeroIndex = irGenerator->generateIntConstant(0);
    auto intIndex = irGenerator->generateIntConstant(arrayPointerType->getNumElementsIndex());
    auto intPointer = llvm::GetElementPtrInst::Create(arrayPointerType->getType(), allocation->getValue(), { zeroIndex, intIndex });
    auto loadedNumElements = new llvm::LoadInst(arrayPointerType->getNumElementsType(), intPointer, "", false, DataAlignmentGenerator::generate(intIndex->getType()));
    auto destinationAllocation = IRInstructionNodeFactory::create(IRPointerType::create(arrayPointerType->getElementIRType()), loadedNumElements);
    auto pointerAllocation = IRInstructionNodeFactory::create(allocation, destinationAllocation);
    return new IRAggregateIdentifierExpressionNode(node, destinationAllocation, pointerAllocation, allocation, intPointer, loadedNumElements, arrayPointerType);
}

IRAggregateIdentifierExpressionNode* IdentifierExpressionIRStrategy::generateForGlobalAggregate(ASTIdentifierExpressionNode* node, IRInstructionNode* allocation, IRGenerator* irGenerator, IRLookupTable* scope, IRContext* irContext, IROperationType irOperationType) {
    auto arrayPointerType = (IRArrayPointerType*)allocation->getIRType()->getSourceType();
    auto zeroIndex = irGenerator->generateIntConstant(0);
    auto intIndex = irGenerator->generateIntConstant(arrayPointerType->getNumElementsIndex());
    auto intPointer = llvm::GetElementPtrInst::Create(arrayPointerType->getType(), allocation->getValue(), { zeroIndex, intIndex });
    auto loadedNumElements = new llvm::LoadInst(arrayPointerType->getNumElementsType(), intPointer, "", false, DataAlignmentGenerator::generate(intIndex->getType()));
    auto mallocSize = llvm::CallInst::Create(
            irContext->getIRModule()->getMallocSizeFunction()->getFunctionType(),
            irContext->getIRModule()->getMallocSizeFunction(),
            {
                    loadedNumElements,
                    irGenerator->generateIntConstant(arrayPointerType->getElementIRType()->getSizeInBytes())
            },
            ""
    );
    auto malloc = llvm::CallInst::Create(
            irContext->getIRModule()->getMallocFunction()->getFunctionType(),
            irContext->getIRModule()->getMallocFunction(),
            { mallocSize },
            ""
    );
    auto mallocAllocation = IRInstructionNodeFactory::create(
            new llvm::BitCastInst(malloc, arrayPointerType->getElementType()),
            irGenerator->generateIrPointerType(arrayPointerType->getElementIRType()),
            { malloc, mallocSize }
    );
    auto pointerAllocation = IRInstructionNodeFactory::create(allocation, mallocAllocation);
    return new IRAggregateIdentifierExpressionNode(node, mallocAllocation, pointerAllocation, allocation, intPointer, loadedNumElements, arrayPointerType);
}