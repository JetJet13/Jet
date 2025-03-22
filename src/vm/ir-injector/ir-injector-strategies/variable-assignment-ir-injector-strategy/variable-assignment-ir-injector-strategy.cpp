//
// Created by Johny Georges on 2025-01-06.
//

#include "variable-assignment-ir-injector-strategy.h"
#include "../../../ir-type/ir-array-pointer-type.h"
#include "../../../utils/data-alignment-generator/data-alignment-generator.h"

void VariableAssignmentIRInjectorStrategy::inject(IRVariableAssignmentStatementNode* irVariableAssignmentStatement, IRBlockNode* irBlock, IRInjector* irInjector, IRModuleNode *irModule, IRLookupTable* scope) {
    auto globalVariable = scope->findGlobalVariable(irVariableAssignmentStatement->getVariableName());
    auto operation = globalVariable.has_value() ? IR_COPY_GLOBAL_ASSIGNMENT_OP : IR_COPY_ASSIGNMENT_OP;
    auto newVariableValue = irInjector
            ->inject(
                    irBlock,
                    irVariableAssignmentStatement->getIRExpression(),
                    operation, irModule, scope);
    if (globalVariable) {
        auto oldGlobalVariableValue = irBlock->getBuilder()->get()->CreateLoad(globalVariable.value()->getAllocatedType(), globalVariable.value()->getValue());
        auto globalVariableIrType = globalVariable.value()->getIRType()->getSourceType();
        irBlock->getBuilder()->get()->CreateMemCpy(
                globalVariable.value()->getValue(),
                DataAlignmentGenerator::generate(globalVariableIrType),
                newVariableValue,
                DataAlignmentGenerator::generate(globalVariableIrType),
                globalVariableIrType->getSizeInBytes()
        );
        this->freeOldMallocs(oldGlobalVariableValue, globalVariable.value(), irBlock, irInjector, irModule, scope);

    } else {
        auto variable = scope->find(irVariableAssignmentStatement->getVariableName()).value();
        auto variableIrType = variable->getIRType()->getSourceType();
        irBlock->getBuilder()->get()->CreateMemCpy(
                variable->getValue(),
                DataAlignmentGenerator::generate(variableIrType),
                newVariableValue,
                DataAlignmentGenerator::generate(variableIrType),
                variableIrType->getSizeInBytes()
        );
    }
}

void VariableAssignmentIRInjectorStrategy::freeOldMallocs(llvm::LoadInst* oldValue, IRInstructionNode* allocation, IRBlockNode* irBlock, IRInjector* irInjector, IRModuleNode* irModule, IRLookupTable* scope) {
    if (allocation->getIRType()->getSourceType()->isArrayPointerType()) {
        auto arrayPointerType = (IRArrayPointerType*)allocation->getIRType()->getSourceType();
        irBlock->getBuilder()->get()->CreateCall(
                irModule->getMallocFreeArrayFunction()->getFunctionType(),
                irModule->getMallocFreeArrayFunction(),
                { irBlock->getBuilder()->get()->getInt32(arrayPointerType->getNumLevels()), oldValue }
        );
    }
}