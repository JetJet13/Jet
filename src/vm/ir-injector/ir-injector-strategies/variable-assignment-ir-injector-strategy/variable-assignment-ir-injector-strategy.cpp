//
// Created by Johny Georges on 2025-01-06.
//

#include "variable-assignment-ir-injector-strategy.h"
#include "../../../ir-type/ir-array-pointer-type.h"
#include "../../../utils/ir-instruction-node-factory/ir-instruction-node-factory.h"

void VariableAssignmentIRInjectorStrategy::inject(IRVariableAssignmentStatementNode* irVariableAssignmentStatement, IRBlockNode* irBlock, IRInjector* irInjector, IRModuleNode *irModule, IRLookupTable* scope) {
    auto globalVariable = scope->findGlobalVariable(irVariableAssignmentStatement->getVariableName());
    auto operation = globalVariable.has_value() ? IR_COPY_GLOBAL_ASSIGNMENT_OP : IR_COPY_ASSIGNMENT_OP;
    auto irExpressionValue = irInjector
            ->inject(
                    irBlock,
                    irVariableAssignmentStatement->getIRExpression(),
                    operation, irModule, scope);
    if (globalVariable) {
        auto mallocsToFree = std::vector<llvm::LoadInst*>();
        this->getMallocsToFree(&mallocsToFree, globalVariable.value(), irBlock, irInjector, irModule, scope);
        irBlock->getBuilder()->get()->CreateStore(
            irExpressionValue,
            globalVariable.value()->getValue()
        );

        for (auto mallocToFree : mallocsToFree) {
            // free the old mallocs after assigning the global variable
            // it's new value
            irBlock->getBuilder()->get()->CreateCall(
                    irModule->getMallocFreeFunction()->getFunctionType(),
                    irModule->getMallocFreeFunction(),
                    { mallocToFree }
            );
        }
    } else {
        irBlock->getBuilder()->get()->CreateStore(
            irExpressionValue,
            scope->find(irVariableAssignmentStatement->getVariableName()).value()->getValue()
        );
    }
}

void VariableAssignmentIRInjectorStrategy::getMallocsToFree(std::vector<llvm::LoadInst*>* mallocsToFree, IRInstructionNode* allocation, IRBlockNode* irBlock, IRInjector* irInjector, IRModuleNode* irModule, IRLookupTable* scope) {
    if (allocation->getIRType()->getSourceType()->isArrayPointerType()) {
        auto zeroIndex = irBlock->getBuilder()->get()->getInt32(0);
        auto arrayPointerType = (IRArrayPointerType*)allocation->getIRType()->getSourceType();
        auto allocIndex = irBlock->getBuilder()->get()->getInt32(arrayPointerType->getAllocIndex());
        auto allocPointer = irBlock->getBuilder()->get()->CreateInBoundsGEP(arrayPointerType->getType(), allocation->getValue(), {zeroIndex, allocIndex });
        mallocsToFree->push_back(irBlock->getBuilder()->get()->CreateLoad(arrayPointerType->getAllocType(), allocPointer));
        if (arrayPointerType->getElementIRType()->getSourceType()->isStructType()) {
            auto allocPointerAllocation = IRInstructionNodeFactory::create(allocPointer, IRPointerType::create(arrayPointerType->getElementIRType()->getSourceType()));
            this->getMallocsToFree(mallocsToFree, allocPointerAllocation, irBlock, irInjector, irModule, scope);
        } else if (arrayPointerType->getElementIRType()->getSourceType()->isArrayPointerType()) {
            auto allocPointerAllocation = IRInstructionNodeFactory::create(allocPointer, IRPointerType::create(arrayPointerType->getElementIRType()->getSourceType()));
            this->getMallocsToFree(mallocsToFree, allocPointerAllocation, irBlock, irInjector, irModule, scope);
        }
    }
}