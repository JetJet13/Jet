//
// Created by Johny Georges on 2024-06-26.
//

#include "identifier-expression-ir-strategy.h"
#include "../../../../utils/data-alignment-generator/data-alignment-generator.h"
#include "../../../../utils/ir-instruction-node-factory/ir-instruction-node-factory.h"
#include "../../../../ir-nodes/ir-expression-nodes/ir-global-identifier-expression-node.h"
#include "../../../../ir-nodes/ir-expression-nodes/ir-identifier-expression-node.h"

IRExpressionNode* IdentifierExpressionIRStrategy::generate(ASTIdentifierExpressionNode* node, IRGenerator* irGenerator, IRLookupTable* scope, IRContext* irContext, IROperationType irOperationType) {
    auto allocation = scope->find(node->getIdentifierNode()->getId());
    if (irOperationType == IR_COPY_ASSIGNMENT_OP && allocation && allocation.value()->getIRType()->getSourceType()->isArrayPointerType()) {
        return this->generateForAggregate(node, allocation.value(), irGenerator, scope, irContext, irOperationType);
    } else if (allocation) {
        return new IRIdentifierExpressionNode(node, allocation.value());
    }

    auto globalVariable = scope->findGlobalVariable(node->getIdentifierNode()->getId()).value();
    if (irOperationType == IR_COPY_ASSIGNMENT_OP && globalVariable->getIRType()->getSourceType()->isArrayPointerType()) {
        return this->generateForGlobalAggregate(node, globalVariable, irGenerator, scope, irContext, irOperationType);
    }
    return new IRGlobalIdentifierExpressionNode(
            node,
            globalVariable,
            IRInstructionNodeFactory::create(globalVariable->getValue())
    );
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

IRAggregateIdentifierExpressionNode* IdentifierExpressionIRStrategy::generateForGlobalAggregate(ASTIdentifierExpressionNode* node, IRGlobalVariableNode* irGlobalVariable, IRGenerator* irGenerator, IRLookupTable* scope, IRContext* irContext, IROperationType irOperationType) {
    // todo: rework this since it's not working
    auto arrayPointerType = (IRArrayPointerType*)irGlobalVariable->getIRType()->getSourceType();
    auto allocation = IRInstructionNodeFactory::create(irGlobalVariable->getValue());
    auto zeroIndex = irGenerator->generateIntConstant(0);
    auto intIndex = irGenerator->generateIntConstant(arrayPointerType->getNumElementsIndex());
    auto intPointer = llvm::GetElementPtrInst::Create(arrayPointerType->getType(), irGlobalVariable->getValue(), { zeroIndex, zeroIndex, intIndex });
    auto loadedNumElements = new llvm::LoadInst(arrayPointerType->getNumElementsType(), intPointer, "", false, DataAlignmentGenerator::generate(intIndex->getType()));
    auto destinationAllocation = IRInstructionNodeFactory::create(IRPointerType::create(arrayPointerType->getElementIRType()), loadedNumElements);
    auto pointerAllocation = IRInstructionNodeFactory::create(allocation, destinationAllocation);
    return new IRAggregateIdentifierExpressionNode(node, destinationAllocation, pointerAllocation, allocation, intPointer, loadedNumElements, arrayPointerType);
}