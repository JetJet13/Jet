//
// Created by Johny Georges on 2026-02-20.
//

#include "ref-value-assignment-ir-injector-strategy.h"
#include "../../../utils/data-alignment-generator/data-alignment-generator.h"
#include "../ir-injector-helpers/instruction-ir-injector-helper/instruction-ir-injector-helper.h"
#include "../../../ir-type/ir-ref-type.h"
#include "../ir-injector-helpers/debug-ir-injector-helper/debug-ir-injector-helper.h"

void RefValueAssignmentIRInjectorStrategy::inject(IRRefValueAssignmentStatementNode* irRefValueAssignmentStatement, IRBlockNode* irBlock, IRInjector* irInjector, std::shared_ptr<IRModuleNode> irModule, IRLookupTable* scope) {
    auto irType = irRefValueAssignmentStatement->getIRExpression()->getUnderlyingIRType();
    auto globalVariable = scope->findGlobalVariable(irRefValueAssignmentStatement->getVariableName());
    auto newValue = irInjector->inject(
            irBlock,
            irRefValueAssignmentStatement->getIRExpression(),
            new IROperation(IR_COPY_ASSIGNMENT_OP),
            irModule,
            scope
    );
    auto newValueMalloc = irBlock->getBuilder()->get()->CreateCall(
        irModule->getMallocFunction(),
        {
            irBlock->getBuilder()->get()->getInt64(1),
            irBlock->getBuilder()->get()->getInt64(irType->getSizeInBytes())
        }
    );
    InstructionIRInjectorHelper::injectStore(newValue, newValueMalloc, irBlock, irType);
    if (globalVariable) {
        auto irRefType = (IRRefType*)globalVariable.value()->getIRType()->getSourceType();
        auto typeValue = irInjector->inject(irBlock, irRefType->getUnderlyingType());
        auto loadedTypeValue = InstructionIRInjectorHelper::injectLoad(irRefType->getUnderlyingType()->getValue()->getAllocatedType(), typeValue, irBlock);
        irBlock->getBuilder()->get()->CreateCall(
            irModule->getSetRefValueFunction(),
            { globalVariable.value()->getValue(), newValueMalloc, loadedTypeValue }
        );
    } else {
        auto variable = scope->find(irRefValueAssignmentStatement->getVariableName()).value();
        auto irRefType = (IRRefType*)variable->getIRType()->getSourceType();
        auto typeValue = irInjector->inject(irBlock, irRefType->getUnderlyingType());
        auto loadedTypeValue = InstructionIRInjectorHelper::injectLoad(irRefType->getUnderlyingType()->getValue()->getAllocatedType(), typeValue, irBlock);
        DebugIRInjectorHelper::injectLog(irBlock, "REF VALUE ASSIGNMENT - FREEING CURRENT VALUE", irInjector, irModule);
        irBlock->getBuilder()->get()->CreateCall(
                irModule->getSetRefValueFunction(),
                { variable->getValue(), newValueMalloc,  loadedTypeValue }
        );
    }
}