//
// Created by Johny Georges on 2025-01-06.
//

#include "variable-assignment-ir-injector-strategy.h"
#include "../../../ir-type/ir-array-pointer-type.h"
#include "../../../utils/ir-instruction-node-factory/ir-instruction-node-factory.h"
#include "../../../../shared/utils/logger/logger.h"

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
        irBlock->getBuilder()->get()->CreateStore(
                newVariableValue,
                globalVariable.value()->getValue()
        );
        this->freeOldMallocs(oldGlobalVariableValue, globalVariable.value(), irBlock, irInjector, irModule, scope);

    } else {
        irBlock->getBuilder()->get()->CreateStore(
                newVariableValue,
                scope->find(irVariableAssignmentStatement->getVariableName()).value()->getValue()
        );
    }
}

void VariableAssignmentIRInjectorStrategy::freeOldMallocs(llvm::LoadInst* oldValue, IRInstructionNode* allocation, IRBlockNode* irBlock, IRInjector* irInjector, IRModuleNode* irModule, IRLookupTable* scope) {
    if (allocation->getIRType()->getSourceType()->isArrayPointerType()) {
        auto levels = 0;
        auto irType = allocation->getIRType()->getSourceType();
        while (irType->isArrayPointerType()) {
            levels++;
            auto arrayPointerType = (IRArrayPointerType*)irType;
            irType = arrayPointerType->getElementIRType();
        }
        irBlock->getBuilder()->get()->CreateCall(
                irModule->getMallocFreeArrayFunction()->getFunctionType(),
                irModule->getMallocFreeArrayFunction(),
                { oldValue }
        );
    }
}