//
// Created by Johny Georges on 2025-01-06.
//

#include "variable-assignment-ir-injector-strategy.h"
#include "../../../ir-type/ir-array-pointer-type.h"

void VariableAssignmentIRInjectorStrategy::inject(IRVariableAssignmentStatementNode* irVariableAssignmentStatement, IRBlockNode* irBlock, IRInjector* irInjector, IRModuleNode *irModule, IRLookupTable* scope) {
    auto irExpressionValue = irInjector
            ->inject(
                    irBlock,
                    irVariableAssignmentStatement->getIRExpression(),
                    IR_OPERAND_OP, irModule, scope);
    auto globalVariable = scope->findGlobalVariable(irVariableAssignmentStatement->getVariableName());
    if (globalVariable) {
        auto loadedAlloc = std::optional<llvm::LoadInst*>();
        if (globalVariable.value()->getIRType()->getSourceType()->isArrayPointerType()) {
            auto zeroIndex = irBlock->getBuilder()->get()->getInt32(0);
            auto arrayPointerType = (IRArrayPointerType*)globalVariable.value()->getIRType()->getSourceType();
            auto allocIndex = irBlock->getBuilder()->get()->getInt32(arrayPointerType->getAllocIndex());
            auto allocPointer = irBlock->getBuilder()->get()->CreateInBoundsGEP(arrayPointerType->getType(), globalVariable.value()->getValue(), { zeroIndex, allocIndex });
            loadedAlloc = irBlock->getBuilder()->get()->CreateLoad(arrayPointerType->getAllocType(), allocPointer);
        }
        irBlock->getBuilder()->get()->CreateStore(
            irExpressionValue,
            globalVariable.value()->getValue()
        );

        if (loadedAlloc) {
            // free the old malloc after assigning the global variable
            // it's new value
            irBlock->getBuilder()->get()->CreateCall(
                    irModule->getMallocFreeFunction()->getFunctionType(),
                    irModule->getMallocFreeFunction(),
                    { loadedAlloc.value() }
            );
        }
    } else {
        irBlock->getBuilder()->get()->CreateStore(
            irExpressionValue,
            scope->find(irVariableAssignmentStatement->getVariableName()).value()->getValue()
        );
    }
}