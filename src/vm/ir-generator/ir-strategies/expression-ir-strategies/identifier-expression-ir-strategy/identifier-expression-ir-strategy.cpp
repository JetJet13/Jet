//
// Created by Johny Georges on 2024-06-26.
//

#include "identifier-expression-ir-strategy.h"
#include "../../../../utils/data-alignment-generator/data-alignment-generator.h"
#include "../../../../utils/ir-instruction-node-factory/ir-instruction-node-factory.h"
#include "../../../../ir-nodes/ir-expression-nodes/ir-global-identifier-expression-node.h"
#include "../../../../ir-nodes/ir-expression-nodes/ir-identifier-expression-node.h"

IRExpressionNode* IdentifierExpressionIRStrategy::generate(ASTIdentifierExpressionNode* node, std::unique_ptr<llvm::LLVMContext>* context, IRGenerator* irGenerator, IRLookupTable* scope, IRModuleNode* irModule, IROperationType irOperationType) {
    auto allocation = scope->find(node->getIdentifierNode()->getId());
    if (irOperationType == IR_COPY_ASSIGNMENT_OP && allocation && allocation.value()->getIRType()->getSourceType()->isArrayPointerType()) {
        return this->generateForAggregate(node, allocation.value(), context, irGenerator, scope, irModule, irOperationType);
    } else if (allocation) {
        return new IRIdentifierExpressionNode(node, allocation.value());
    }

    auto globalVariable = scope->findGlobalVariable(node->getIdentifierNode()->getId()).value();
    return new IRGlobalIdentifierExpressionNode(
            node,
            globalVariable,
            IRInstructionNodeFactory::create(globalVariable->getValue())
    );
}

IRAggregateIdentifierExpressionNode* IdentifierExpressionIRStrategy::generateForAggregate(ASTIdentifierExpressionNode* node, IRInstructionNode* allocation, std::unique_ptr<llvm::LLVMContext>* context, IRGenerator* irGenerator, IRLookupTable* scope, IRModuleNode* irModule, IROperationType irOperationType) {
    auto arrayPointerType = (IRArrayPointerType*)allocation->getIRType()->getSourceType();
    auto zeroIndex = irGenerator->generateIntConstant(0);
    auto intIndex = irGenerator->generateIntConstant(arrayPointerType->getNumElementsIndex());
    auto intPointer = llvm::GetElementPtrInst::Create(arrayPointerType->getType(), allocation->getValue(), { zeroIndex, intIndex });
    auto loadedNumElements = new llvm::LoadInst(arrayPointerType->getNumElementsType(), intPointer, "", false, DataAlignmentGenerator::generate(intIndex->getType()));
    auto destinationAllocation = IRInstructionNodeFactory::create(IRPointerType::create(arrayPointerType->getElementIRType()), loadedNumElements);
    auto pointerAllocation = IRInstructionNodeFactory::create(allocation, destinationAllocation);
    return new IRAggregateIdentifierExpressionNode(node, destinationAllocation, pointerAllocation, allocation, intPointer, loadedNumElements, arrayPointerType);
}