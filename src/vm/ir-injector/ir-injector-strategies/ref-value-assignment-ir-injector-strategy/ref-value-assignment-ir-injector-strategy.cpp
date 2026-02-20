//
// Created by Johny Georges on 2026-02-20.
//

#include "ref-value-assignment-ir-injector-strategy.h"
#include "../../../utils/data-alignment-generator/data-alignment-generator.h"
#include "../ir-injector-helpers/instruction-ir-injector-helper/instruction-ir-injector-helper.h"
#include "../../../ir-type/ir-ref-type.h"

void RefValueAssignmentIRInjectorStrategy::inject(IRRefValueAssignmentStatementNode* irRefValueAssignmentStatement, IRBlockNode* irBlock, IRInjector* irInjector, std::shared_ptr<IRModuleNode> irModule, IRLookupTable* scope) {
    auto globalVariable = scope->findGlobalVariable(irRefValueAssignmentStatement->getVariableName());
    auto newVariableValue = irInjector->inject(
            irBlock,
            irRefValueAssignmentStatement->getIRExpression(),
            new IROperation(IR_COPY_ASSIGNMENT_OP),
            irModule,
            scope
    );
    if (globalVariable) {
        auto globalVariableIrType = (IRRefType*)globalVariable.value()->getIRType()->getSourceType();
        auto newValueAlloc = irBlock->getBuilder()->get()->CreateAlloca(globalVariableIrType->getType());
        InstructionIRInjectorHelper::injectStore(newVariableValue, newValueAlloc, irBlock, globalVariableIrType);
        auto typeValue = irInjector->inject(irBlock, globalVariableIrType->getUnderlyingType());
        auto loadedTypeValue = InstructionIRInjectorHelper::injectLoad(globalVariableIrType->getUnderlyingType()->getValue()->getAllocatedType(), typeValue, irBlock);
        auto pointerToRefValue = irBlock->getBuilder()->get()->CreateStructGEP(globalVariableIrType->getType(), globalVariable.value()->getValue(), globalVariableIrType->getRefValueIndex());
        auto loadedPointerToRefValue = InstructionIRInjectorHelper::injectLoad(globalVariableIrType->getRefValueType(), pointerToRefValue, irBlock);
        if (globalVariableIrType->getUnderlyingType()->containsTypeThatRequiresFreeing()) {
            irBlock->getBuilder()->get()->CreateCall(
                    irModule->getFreeValueFunction(),
                    { loadedPointerToRefValue, loadedTypeValue }
            );
        }
        irBlock->getBuilder()->get()->CreateMemCpy(
                loadedPointerToRefValue,
                globalVariableIrType->getUnderlyingType()->getAlignment(),
                newValueAlloc,
                globalVariableIrType->getUnderlyingType()->getAlignment(),
                globalVariableIrType->getUnderlyingType()->getSizeInBytes()
        );
    } else {
        auto variable = scope->find(irRefValueAssignmentStatement->getVariableName()).value();
        auto irRefType = (IRRefType*)variable->getIRType()->getSourceType();
        auto pointerToRefValue = irBlock->getBuilder()->get()->CreateStructGEP(irRefType->getType(), variable->getValue(), irRefType->getRefValueIndex());
        auto loadedPointerToRefValue = InstructionIRInjectorHelper::injectLoad(irRefType->getRefValueType(), pointerToRefValue, irBlock);
        if (irRefType->getUnderlyingType()->containsTypeThatRequiresFreeing()) {
            auto typeValue = irInjector->inject(irBlock, irRefType->getUnderlyingType());
            auto loadedTypeValue = InstructionIRInjectorHelper::injectLoad(irRefType->getUnderlyingType()->getValue()->getAllocatedType(), typeValue, irBlock);
            irBlock->getBuilder()->get()->CreateCall(
                    irModule->getFreeValueFunction(),
                    { loadedPointerToRefValue, loadedTypeValue }
            );
        }
        InstructionIRInjectorHelper::injectStore(newVariableValue, loadedPointerToRefValue, irBlock, irRefValueAssignmentStatement->getIRExpression()->getIRType());
    }
}